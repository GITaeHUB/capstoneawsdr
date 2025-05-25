#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include "motor_control/msg/servo_ctrl_msg.hpp"
#include "rplidar_ros/msg/object_info.hpp"
#include "rplidar_ros/msg/object_info_array.hpp"
#include <memory>
#include <string>
#include <vector>

class LaneDetectionNode : public rclcpp::Node {
public:
    LaneDetectionNode() : Node("lane_detection_node") {
        RCLCPP_INFO(this->get_logger(), "Lane Detection Node with BEV started");

        image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/display_mjpeg", 1,
            std::bind(&LaneDetectionNode::image_callback, this, std::placeholders::_1));

        object_sub_ = this->create_subscription<rplidar_ros::msg::ObjectInfoArray>(
            "/obstacle_info", 1,
            std::bind(&LaneDetectionNode::object_callback, this, std::placeholders::_1));

        servo_pub_ = this->create_publisher<motor_control::msg::ServoCtrlMsg>("/servo_cmd", 1);

        src_[0] = cv::Point2f(70,145); src_[1] = cv::Point2f(110,100);
        src_[2] = cv::Point2f(240,100); src_[3] = cv::Point2f(300,145);
        dst_[0] = cv::Point2f(90,220); dst_[1] = cv::Point2f(90,20);
        dst_[2] = cv::Point2f(230,20); dst_[3] = cv::Point2f(230,220);
        warp_matrix_ = cv::getPerspectiveTransform(src_, dst_);

        prev_mid_x_ = 160;  // 초기 중앙값
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg) {
        try {
            cv::Mat frame = cv_bridge::toCvCopy(msg, "bgr8")->image;
            cv::resize(frame, frame, cv::Size(320, 240));

            cv::Mat hsv, yellow_mask, white_mask, binary;
            cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
            cv::inRange(hsv, cv::Scalar(5, 100, 100), cv::Scalar(20, 255, 255), yellow_mask);
            cv::inRange(hsv, cv::Scalar(0, 0, 200),  cv::Scalar(180, 40, 255), white_mask);
            cv::bitwise_or(yellow_mask, white_mask, binary);

            cv::Mat birdview_gray;
            cv::warpPerspective(binary, birdview_gray, warp_matrix_, binary.size(), cv::INTER_NEAREST);
            cv::Mat birdview_yellow;
            cv::warpPerspective(yellow_mask, birdview_yellow, warp_matrix_, yellow_mask.size(), cv::INTER_NEAREST);
            cv::Mat birdview_color;
            cv::cvtColor(birdview_gray, birdview_color, cv::COLOR_GRAY2BGR);

            int window_height = 40;
            int margin = 30;
            int minpix = 20;
            int num_windows = 6;

            int height = birdview_gray.rows, width = birdview_gray.cols;
            int left_x = 80, right_x = 240;
            std::vector<int> left_centers, right_centers;

            // 좌우 yellow 픽셀 개수: 하단 절반 영역만 계산
            int yellow_left = 0, yellow_right = 0;
            for (int y = height / 2; y < height; ++y) {
                const uchar* row_ptr = birdview_yellow.ptr<uchar>(y);
                for (int x = 0; x < width / 2; ++x) {
                    if (row_ptr[x] > 0) yellow_left++;
                }
                for (int x = width / 2; x < width; ++x) {
                    if (row_ptr[x] > 0) yellow_right++;
                }
            }

            for (int i = 0; i < num_windows; ++i) {
                int y_low = height - (i + 1) * window_height;
                int y_high = height - i * window_height;

                int lx_low = std::max(0, left_x - margin), lx_high = std::min(width, left_x + margin);
                int rx_low = std::max(0, right_x - margin), rx_high = std::min(width, right_x + margin);

                cv::Rect left_win(lx_low, y_low, lx_high - lx_low, y_high - y_low);
                cv::Rect right_win(rx_low, y_low, rx_high - rx_low, y_high - y_low);

                int lx_sum = 0, lx_count = 0;
                int rx_sum = 0, rx_count = 0;

                for (int row = 0; row < left_win.height; ++row) {
                    const uchar* ptr = birdview_gray.ptr<uchar>(y_low + row) + lx_low;
                    for (int col = 0; col < lx_high - lx_low; ++col) {
                        if (ptr[col] > 0) {
                            lx_sum += col;
                            lx_count++;
                        }
                    }
                }
                if (lx_count > minpix)
                    left_x = lx_low + lx_sum / lx_count;

                for (int row = 0; row < right_win.height; ++row) {
                    const uchar* ptr = birdview_gray.ptr<uchar>(y_low + row) + rx_low;
                    for (int col = 0; col < rx_high - rx_low; ++col) {
                        if (ptr[col] > 0) {
                            rx_sum += col;
                            rx_count++;
                        }
                    }
                }
                if (rx_count > minpix)
                    right_x = rx_low + rx_sum / rx_count;

                left_centers.push_back(left_x);
                right_centers.push_back(right_x);

                cv::rectangle(birdview_color, left_win, cv::Scalar(0,255,0), 2);
                cv::rectangle(birdview_color, right_win, cv::Scalar(255,0,0), 2);
            }

            // fallback 로직 적용
            int mid_x;
            size_t idx = 3;
            if (left_centers.size() > idx && right_centers.size() > idx) {
                mid_x = (left_centers[idx] + right_centers[idx]) / 2;
            } else if (left_centers.size() > idx) {
                mid_x = left_centers[idx] + 100;
            } else if (right_centers.size() > idx) {
                mid_x = right_centers[idx] - 100;
            } else {
                mid_x = prev_mid_x_;
            }
            prev_mid_x_ = mid_x;

            int mid_y = height - (num_windows / 2) * window_height - window_height / 2;
            cv::circle(birdview_color, cv::Point(mid_x, mid_y), 5, cv::Scalar(0,0,255), -1);

            double error = mid_x - (width / 2.0);
            double angle = error / (width / 2.0) * 4.0;

            motor_control::msg::ServoCtrlMsg ctrl_msg;
            ctrl_msg.angle = angle;
            ctrl_msg.throttle = 0.25;
            servo_pub_->publish(ctrl_msg);

            cv::imshow("Binary with Windows", birdview_color);
            cv::waitKey(1);
        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception: %s", e.what());
        }
    }

    void object_callback(const rplidar_ros::msg::ObjectInfoArray::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received %lu obstacles", msg->objects.size());
        if (!msg->objects.empty()) {
            const auto& obs = msg->objects[0];
            float x = -obs.x;
            float y = -obs.y;
            double angle_rad = std::atan2(y, x);
            double angle_deg = angle_rad * 180.0 / M_PI;
            std::string position;
            if (x > 0 && y > 0)
                position = "Front-Left";
            else if (x > 0 && y < 0)
                position = "Front-Right";
            else
                position = "Not in front sector";
            RCLCPP_INFO(this->get_logger(), "Nearest Obstacle: x=%.2f, y=%.2f, dist=%.2f", obs.x, obs.y, obs.distance);
            RCLCPP_INFO(this->get_logger(), ">> Transformed x=%.2f, y=%.2f -> %s, angle=%.2f deg", x, y, position.c_str(), std::abs(angle_deg));
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Subscription<rplidar_ros::msg::ObjectInfoArray>::SharedPtr object_sub_;
    rclcpp::Publisher<motor_control::msg::ServoCtrlMsg>::SharedPtr servo_pub_;
    cv::Point2f src_[4], dst_[4];
    cv::Mat warp_matrix_;
    int prev_mid_x_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LaneDetectionNode>());
    rclcpp::shutdown();
    return 0;
}
