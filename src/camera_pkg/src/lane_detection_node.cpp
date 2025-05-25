#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include "motor_control/msg/servo_ctrl_msg.hpp"
#include "rplidar_ros/msg/object_info_array.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "std_msgs/msg/string.hpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class LaneDetectionNode : public rclcpp::Node {
public:
    LaneDetectionNode() : Node("lane_detection_node") {
        image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/display_mjpeg", 1,
            std::bind(&LaneDetectionNode::image_callback, this, std::placeholders::_1));

        object_sub_ = this->create_subscription<rplidar_ros::msg::ObjectInfoArray>(
            "/obstacle_info", 1,
            std::bind(&LaneDetectionNode::object_callback, this, std::placeholders::_1));
            

        servo_pub_ = this->create_publisher<motor_control::msg::ServoCtrlMsg>("/servo_cmd", 1);

        log_pub_ = this->create_publisher<std_msgs::msg::String>("/log_topic", 1);


        src_[0] = cv::Point2f(70, 145); src_[1] = cv::Point2f(110, 100);
        src_[2] = cv::Point2f(240, 100); src_[3] = cv::Point2f(300, 145);
        dst_[0] = cv::Point2f(90, 220); dst_[1] = cv::Point2f(90, 20);
        dst_[2] = cv::Point2f(230, 20); dst_[3] = cv::Point2f(230, 220);
        warp_matrix_ = cv::getPerspectiveTransform(src_, dst_);
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg) {
        try {
            cv::Mat frame = cv_bridge::toCvCopy(msg, "bgr8")->image;
            cv::resize(frame, frame, cv::Size(320, 240));

            cv::Mat hsv, yellow_mask, white_mask, binary;
            cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
            cv::inRange(hsv, cv::Scalar(5, 100, 100), cv::Scalar(20, 255, 255), yellow_mask);
            cv::inRange(hsv, cv::Scalar(0, 0, 200), cv::Scalar(180, 40, 255), white_mask);
            // cv::inRange(hsv, cv::Scalar(0, 0, 200), cv::Scalar(180, 40, 255), yellow_mask);
            cv::bitwise_or(yellow_mask, white_mask, binary);
            cv::Mat hsv_to_bgr;
            cv::cvtColor(hsv, hsv_to_bgr, cv::COLOR_HSV2BGR);

            // [추가] 시각화용 윈도우 출력
            // cv::imshow("Original Frame", frame);
            // cv::imshow("HSV as BGR", hsv_to_bgr);
            // cv::imshow("Yellow Mask", yellow_mask);
            // cv::imshow("White Mask", white_mask);

            cv::Mat birdview_gray;
            cv::warpPerspective(binary, birdview_gray, warp_matrix_, binary.size(), cv::INTER_NEAREST);
            cv::Mat birdview_color;
            cv::cvtColor(birdview_gray, birdview_color, cv::COLOR_GRAY2BGR);

            int window_height = 40, margin = 35, minpix = 10, num_windows = 6;
            int width = birdview_gray.cols, height = birdview_gray.rows;
            // RCLCPP_INFO(this->get_logger(), "[w] %d  [h=]%d y",
            //            width, height);
            int left_x = 80, right_x = 240;
            std::vector<int> left_centers, right_centers;

            int white_left = 0, yellow_left = 0, white_right = 0, yellow_right = 0;

            for (int i = 0; i < num_windows; ++i) {
                int y_low = height - (i + 1) * window_height;
                int y_high = height - i * window_height;
                int lx_low = std::max(0, left_x - margin), lx_high = std::min(width, left_x + margin);
                int rx_low = std::max(0, right_x - margin), rx_high = std::min(width, right_x + margin);
                cv::Rect left_win(lx_low, y_low, lx_high - lx_low, y_high - y_low);
                cv::Rect right_win(rx_low, y_low, rx_high - rx_low, y_high - y_low);

                white_left  += cv::countNonZero(white_mask(left_win));
                yellow_left += cv::countNonZero(yellow_mask(left_win));
                white_right  += cv::countNonZero(white_mask(right_win));
                yellow_right += cv::countNonZero(yellow_mask(right_win));

                cv::rectangle(birdview_color, left_win, cv::Scalar(0, 255, 0), 2);
                cv::rectangle(birdview_color, right_win, cv::Scalar(255, 0, 0), 2);

                int lx_sum = 0, lx_count = 0, rx_sum = 0, rx_count = 0;
                for (int row = 0; row < left_win.height; ++row) {
                    const uchar* ptr = birdview_gray.ptr<uchar>(y_low + row) + lx_low;
                    for (int col = 0; col < lx_high - lx_low; ++col) {
                        if (ptr[col] > 0) { lx_sum += col; lx_count++; }
                    }
                }
                if (lx_count > minpix) {
                    left_x = lx_low + lx_sum / lx_count;
                    left_centers.push_back(left_x);
                }

                for (int row = 0; row < right_win.height; ++row) {
                    const uchar* ptr = birdview_gray.ptr<uchar>(y_low + row) + rx_low;
                    for (int col = 0; col < rx_high - rx_low; ++col) {
                        if (ptr[col] > 0) { rx_sum += col; rx_count++; }
                    }
                }
                if (rx_count > minpix) {
                    right_x = rx_low + rx_sum / rx_count;
                    right_centers.push_back(right_x);
                }
            }

            // if (white_left > white_right)
            //     current_lane_ = "left_lane";
            // else if (white_left < white_right)
            //     current_lane_ = "right_lane";
            // else
            //     current_lane_ = "unknown";
          
            if (yellow_left < yellow_right){
                current_lane_ = "left_lane";

            }
                
            else if (yellow_left > yellow_right){
                current_lane_ = "right_lane";

            }
                
            else{
                current_lane_ = "unknown";
                // current_lane_ = previous_lane_;
            
            
            }
            // previous_lane_ = current_lane_;
            int mid_x;
            size_t idx = 3;   // window index
            if (left_centers.size() > idx && right_centers.size() > idx)
                mid_x = (left_centers[idx] + right_centers[idx]) / 2;
            else if (left_centers.size() > idx)
                mid_x = left_centers[idx] + 80;
            else if (right_centers.size() > idx)
                mid_x = right_centers[idx] - 85;
            else
                mid_x = 160;

            int mid_y = height - (idx + 0.5) * window_height;
            cv::circle(birdview_color, cv::Point(mid_x, mid_y), 5, cv::Scalar(0, 0, 255), -1);

            double error = mid_x - (width / 2.0);
            double angle = error / (width / 2.0) * 3.3;

            // 회피 중이 아니면 정상 조향
            if (!is_avoiding_ || (this->now() - avoid_start_time_) >= avoid_duration_) {
                is_avoiding_ = false;
                motor_control::msg::ServoCtrlMsg msg;
                msg.angle = angle;
                msg.throttle = 0.53;
                servo_pub_->publish(msg);
            }

            // 디버깅 출력
            // RCLCPP_INFO(this->get_logger(), "[Lane] %s | L:white=%d yellow=%d, R:white=%d yellow=%d",
            //             current_lane_.c_str(), white_left, yellow_left, white_right, yellow_right);
            // RCLCPP_INFO(this->get_logger(), "[Angle] %.2f", angle);

            cv::imshow("Binary with Windows", birdview_color);
            cv::waitKey(1);

        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception: %s", e.what());
        }
    }

    void object_callback(const rplidar_ros::msg::ObjectInfoArray::SharedPtr msg) {

        auto log_msg = std_msgs::msg::String();
        std::stringstream ss;
        ss << "is avoiding" << is_avoiding_;
        log_msg.data = ss.str();
        log_pub_->publish(log_msg);

        if (is_avoiding_) return;

            
        rplidar_ros::msg::ObjectInfo closest_obs;
        bool found = false;
        float min_x = 0.6;
    
        for (const auto& obs : msg->objects) {
            float x = -obs.x;  // 라이다 장착 반대이므로 부호 반전
            float y = -obs.y;
    
            if (x > 0 && x < min_x && std::abs(y) < 0.13) {
                min_x = x;
                closest_obs = obs;
                found = true;
            }
        }
    
        if (found) {
            float x = -closest_obs.x;
            float y = -closest_obs.y;
            RCLCPP_INFO(this->get_logger(), "[Obstacle] Closest at x=%.2f, y=%.2f", x, y);
    
            motor_control::msg::ServoCtrlMsg avoid;
            avoid.throttle = 0.52;
    
            if (current_lane_ == "left_lane") {
                avoid.angle = 1.0;  // 우측 회피
            } else if (current_lane_ == "right_lane") {
                avoid.angle = -1.0; // 좌측 회피
            } else {
                avoid.angle = 0.0;
            }
    
            servo_pub_->publish(avoid);
            is_avoiding_ = true;
            avoid_start_time_ = this->now();
        }
    }

    
    

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Subscription<rplidar_ros::msg::ObjectInfoArray>::SharedPtr object_sub_;
    rclcpp::Publisher<motor_control::msg::ServoCtrlMsg>::SharedPtr servo_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr log_pub_;

    std::string current_lane_ = "unknown";
    // std::string previous_lane_ = "unknown";
    bool is_avoiding_ = false;
    rclcpp::Time avoid_start_time_;
    const rclcpp::Duration avoid_duration_ = rclcpp::Duration::from_seconds(1.5); // 2s is too small

    cv::Point2f src_[4], dst_[4];
    cv::Mat warp_matrix_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LaneDetectionNode>());
    rclcpp::shutdown();
    return 0;
}

// auto msg = std_msgs::msg::String();
// std::stringstream ss;
// ss << "want message" << want msg << "want message"...;
// msg.data = ss.str;
// log_pub_->publish(msg);
// RCLCPP_INFO(this->get_logger(), "obstacle");