#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

#include <thread>
#include <atomic>
#include <memory>

#define DEFAULT_IMAGE_WIDTH 640 //160
#define DEFAULT_IMAGE_HEIGHT 480 //120

class CameraNode : public rclcpp::Node
{
public:
    CameraNode(const std::string & node_name, const std::vector<int> cameraIdxList)
    : Node(node_name), produceFrames_(false), resizeImages_(true)
    {
        RCLCPP_INFO(this->get_logger(), "%s started", node_name.c_str());

        this->declare_parameter<bool>("resize_images", resizeImages_);
        resizeImages_ = this->get_parameter("resize_images").as_bool();

        scanCameraIndex(cameraIdxList);

        displayPub_ = this->create_publisher<sensor_msgs::msg::Image>("display_mjpeg", 10);

        // 서비스 제거 → 자동 스트리밍 시작
        produceFrames_ = true;
        videoWorker_ = std::thread([&]{produceFrames();});
    }

    ~CameraNode()
    {
        produceFrames_ = false;
        if (videoWorker_.joinable()) {
            videoWorker_.join();
        }
    }

private:
    void scanCameraIndex(const std::vector<int> cameraIdxList)
    {
        for (auto idx : cameraIdxList){
            RCLCPP_INFO(this->get_logger(), "Scanning Camera Index %d ", idx);
            cv::VideoCapture cap(idx, cv::CAP_V4L);
            cv::Mat test_frame;
            cap >> test_frame;

            if (test_frame.empty() || !cap.isOpened()) {
                RCLCPP_ERROR(this->get_logger(), "Unable to create video capture stream on index: %d", idx);
                continue;
            }

            cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
            videoCaptureList_.push_back(cap);
            videoIndexList_.push_back(idx);
        }

        switch (videoIndexList_.size()) {
            case 0:
                RCLCPP_ERROR(this->get_logger(), "[Camera Package] No cameras detected.");
                break;
            case 1:
                RCLCPP_INFO(this->get_logger(), "[Camera Package] Single Camera Detected at index: %d", videoIndexList_[0]);
                break;
            case 2:
                RCLCPP_INFO(this->get_logger(), "[Camera Package] Stereo Cameras Detected at indexes: %d, %d", videoIndexList_[0], videoIndexList_[1]);
                break;
            default:
                RCLCPP_ERROR(this->get_logger(), "[Camera Package] Error while detecting cameras.");
        }
    }

    void produceFrames()
    {
        while (produceFrames_) {
            for (auto& cap : videoCaptureList_) {
                if (!cap.isOpened()) {
                    continue;
                }

                cv::Mat frame;
                cap >> frame;

                if (frame.empty()) {
                    RCLCPP_ERROR(this->get_logger(), "No frame returned. Check if camera is plugged in correctly.");
                    continue;
                }

                try {
                    if (resizeImages_) {
                        cv::resize(frame, frame, cv::Size(DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT));
                    }
                    auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
                    msg->header.frame_id = "map";
                    msg->header.stamp = this->now();
                    displayPub_->publish(*msg);

                    // cv::imshow("Camera View", frame);
                    // cv::waitKey(1);  // 1ms 동안 대기 (실시간으로 업데이트)
                    
                } catch (cv_bridge::Exception& e) {
                    RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
                    return;
                }
            }

            rclcpp::sleep_for(std::chrono::milliseconds(33)); // 약 30FPS
        }
    }

    std::vector<cv::VideoCapture> videoCaptureList_;
    std::vector<int> videoIndexList_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr displayPub_;
    std::atomic<bool> produceFrames_;
    std::atomic<bool> resizeImages_;
    std::thread videoWorker_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    std::vector<int> cameraIndex {0, 1};  // /dev/video0, /dev/video1
    rclcpp::spin(std::make_shared<CameraNode>("camera_node", cameraIndex));

    rclcpp::shutdown();
    return 0;
}
