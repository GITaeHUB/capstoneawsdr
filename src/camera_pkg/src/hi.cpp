// 주요 변경 내용:
// 1️⃣ Sliding window는 노랑/흰 구분 없이 중앙 추종용으로만 사용
// 2️⃣ 왼쪽/오른쪽 차선 구분은 warp된 yellow mask 전체에서 좌우 절반 픽셀 수만으로 계산
// 3️⃣ 최종 타겟점을 빨간색 원으로 시각화 추가

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include "motor_control/msg/servo_ctrl_msg.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class LaneDetectionNode : public rclcpp::Node {
public:
    LaneDetectionNode() : Node("lane_detection_node") {
        image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/display_mjpeg", 1,
            std::bind(&LaneDetectionNode::image_callback, this, std::placeholders::_1));

        laser_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 1,
            std::bind(&LaneDetectionNode::laser_callback, this, std::placeholders::_1));

        servo_pub_ = this->create_publisher<motor_control::msg::ServoCtrlMsg>("/servo_cmd", 1);
        log_pub_ = this->create_publisher<std_msgs::msg::String>("/log_topic", 1);

        src_[0] = cv::Point2f(70, 145); src_[1] = cv::Point2f(110, 100);
        src_[2] = cv::Point2f(240, 100); src_[3] = cv::Point2f(300, 145);
        dst_[0] = cv::Point2f(90, 220); dst_[1] = cv::Point2f(90, 20);
        dst_[2] = cv::Point2f(230, 20); dst_[3] = cv::Point2f(230, 220);
        warp_matrix_ = cv::getPerspectiveTransform(src_, dst_);

        start_time_ = this->now();
        prev_mid_x_ = 160;
        prev_angle_ = 0.0;
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
            cv::bitwise_or(yellow_mask, white_mask, binary);

            cv::Mat birdview_gray, yellow_warp;
            cv::warpPerspective(binary, birdview_gray, warp_matrix_, binary.size(), cv::INTER_NEAREST);
            cv::warpPerspective(yellow_mask, yellow_warp, warp_matrix_, yellow_mask.size(), cv::INTER_NEAREST);

            int width = birdview_gray.cols, height = birdview_gray.rows;
            int window_height = 40, num_windows = 6, margin = 40, minpix = 10;
            float alpha = 1.2f;

            int left_x = 80, right_x = 240;
            int prev_left_x = left_x, prev_right_x = right_x;
            std::vector<int> left_centers, right_centers;

            for (int i = 0; i < num_windows; ++i) {
                int y_low = height - (i + 1) * window_height;
                int y_high = height - i * window_height;

                int lx_low = std::max(0, left_x - margin);
                int lx_high = std::min(width, left_x + margin);
                int rx_low = std::max(0, right_x - margin);
                int rx_high = std::min(width, right_x + margin);

                int y_low_clamped = std::max(0, y_low);
                int y_high_clamped = std::min(height, y_high);

                cv::Rect left_win(lx_low, y_low_clamped, lx_high - lx_low, y_high_clamped - y_low_clamped);
                cv::Rect right_win(rx_low, y_low_clamped, rx_high - rx_low, y_high_clamped - y_low_clamped);

                cv::rectangle(birdview_gray, left_win, cv::Scalar(255), 2);
                cv::rectangle(birdview_gray, right_win, cv::Scalar(255), 2);

                int lx_sum = 0, lx_count = 0, rx_sum = 0, rx_count = 0;
                for (int row = 0; row < left_win.height; ++row) {
                    const uchar* ptr = birdview_gray.ptr<uchar>(y_low_clamped + row) + lx_low;
                    for (int col = 0; col < left_win.width; ++col) {
                        if (ptr[col] > 0) { lx_sum += col; lx_count++; }
                    }
                }
                if (lx_count > minpix) {
                    int current_left_x = lx_low + lx_sum / lx_count;
                    int delta = current_left_x - prev_left_x;
                    left_x = current_left_x + static_cast<int>(alpha * delta);
                    prev_left_x = current_left_x;
                    left_centers.push_back(left_x);
                }

                for (int row = 0; row < right_win.height; ++row) {
                    const uchar* ptr = birdview_gray.ptr<uchar>(y_low_clamped + row) + rx_low;
                    for (int col = 0; col < right_win.width; ++col) {
                        if (ptr[col] > 0) { rx_sum += col; rx_count++; }
                    }
                }
                if (rx_count > minpix) {
                    int current_right_x = rx_low + rx_sum / rx_count;
                    int delta = current_right_x - prev_right_x;
                    right_x = current_right_x + static_cast<int>(alpha * delta);
                    prev_right_x = current_right_x;
                    right_centers.push_back(right_x);
                }
            }

            // 타겟 중앙 좌표 계산
            int mid_x;
            size_t idx = 3;
            if (left_centers.size() > idx && right_centers.size() > idx)
                mid_x = (left_centers[idx] + right_centers[idx]) / 2;
            else if (left_centers.size() > idx)
                mid_x = left_centers[idx] + 90;
            else if (right_centers.size() > idx)
                mid_x = right_centers[idx] - 90;
            else
                mid_x = prev_mid_x_;

            cv::circle(birdview_gray, cv::Point(mid_x, height / 2), 5, cv::Scalar(128), -1);

            // 좌우 yellow 픽셀 계산
            int yellow_left = 0, yellow_right = 0;
            for (int y = 0; y < height; ++y) {
                const uchar* row_ptr = yellow_warp.ptr<uchar>(y);
                for (int x = 0; x < width; ++x) {
                    if (row_ptr[x] > 0) {
                        if (x < width / 2) yellow_left++;
                        else yellow_right++;
                    }
                }
            }

            std_msgs::msg::String log_msg;
            log_msg.data = "Current lane decision: " + current_lane_ + ", Left yellow: " + std::to_string(yellow_left) + ", Right yellow: " + std::to_string(yellow_right);
            log_pub_->publish(log_msg);

            if (yellow_left < yellow_right)
                lane_history_.push_back("left_lane");
            else if (yellow_left > yellow_right)
                lane_history_.push_back("right_lane");
            else
                lane_history_.push_back("unknown");

            if (lane_history_.size() > lane_history_size_)
                lane_history_.pop_front();

            int left_count_hist = std::count(lane_history_.begin(), lane_history_.end(), "left_lane");
            int right_count_hist = std::count(lane_history_.begin(), lane_history_.end(), "right_lane");

            if (static_cast<double>(left_count_hist) / lane_history_.size() > trust_threshold_)
                current_lane_ = "left_lane";
            else if (static_cast<double>(right_count_hist) / lane_history_.size() > trust_threshold_)
                current_lane_ = "right_lane";
            else
                current_lane_ = "unknown";

            double error = mid_x - (width / 2.0);
            double error_normalized = error / (width / 2.0);
            double max_angle = 1.3;
            double k = 2.0;
            double angle;
            
            if (mid_x == prev_mid_x_) {
                angle = prev_angle_;
            } else {
                angle = max_angle * (1 - std::exp(-k * std::abs(error_normalized))) * (error_normalized >= 0 ? 1 : -1);
                prev_mid_x_ = mid_x;
                prev_angle_ = angle;
            }

            if (!is_avoiding_ || (this->now() - avoid_start_time_) >= avoid_duration_) {
                is_avoiding_ = false;
                motor_control::msg::ServoCtrlMsg msg;
                msg.angle = angle;
                msg.throttle = 0.55;
                servo_pub_->publish(msg);
            }

            cv::imshow("Birdview with Target", birdview_gray);
            cv::waitKey(1);

        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception: %s", e.what());
        }
    }

    void laser_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
        if (is_avoiding_) {
            auto elapsed = this->now() - avoid_start_time_;
            auto remaining = avoid_duration_ - elapsed;

            if (remaining.seconds() <= 0.1 && remaining.seconds() > 0.0) {
                motor_control::msg::ServoCtrlMsg reverse_msg;
                reverse_msg.throttle = 0.53;

                if (last_avoid_angle_ > 0)
                    reverse_msg.angle = -0.5;
                else if (last_avoid_angle_ < 0)
                    reverse_msg.angle = 0.5;
                else
                    reverse_msg.angle = 0.0;

                servo_pub_->publish(reverse_msg);
            }
            return;
        }

        bool found = false;

        for (size_t i = 0; i < msg->ranges.size(); ++i) {
            float angle = msg->angle_min + i * msg->angle_increment;
            float r = msg->ranges[i];

            if (std::isnan(r) || std::isinf(r)) continue;

            float x = -(r * cos(angle));
            float y = -(r * sin(angle));

            if (x > 0.1 && x < 0.8 && std::abs(y) < 0.2) {
                found = true;
                break;
            }
        }

        if (found) {
            motor_control::msg::ServoCtrlMsg avoid;
            avoid.throttle = 0.53;

            if (current_lane_ == "left_lane") {
                avoid.angle = 1.0;
            } else if (current_lane_ == "right_lane") {
                avoid.angle = -1.0;
            } else {
                avoid.angle = 0.0;
            }

            last_avoid_angle_ = avoid.angle;
            servo_pub_->publish(avoid);
            is_avoiding_ = true;
            avoid_start_time_ = this->now();
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
    rclcpp::Publisher<motor_control::msg::ServoCtrlMsg>::SharedPtr servo_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr log_pub_;

    std::string current_lane_ = "unknown";
    bool is_avoiding_ = false;
    rclcpp::Time avoid_start_time_;
    const rclcpp::Duration avoid_duration_ = rclcpp::Duration::from_seconds(0.4);
    double last_avoid_angle_ = 0.0;

    std::deque<std::string> lane_history_;
    const size_t lane_history_size_ = 10;
    const double trust_threshold_ = 0.6;

    rclcpp::Time start_time_;
    int prev_mid_x_;
    double prev_angle_;

    cv::Point2f src_[4], dst_[4];
    cv::Mat warp_matrix_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LaneDetectionNode>());
    rclcpp::shutdown();
    return 0;
}

다시 한번 전체적으로 코드 흐름 읊어봐