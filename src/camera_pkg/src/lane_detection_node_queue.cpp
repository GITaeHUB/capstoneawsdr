#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include "motor_control/msg/servo_ctrl_msg.hpp"
// #include "rplidar_ros/msg/object_info_array.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
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

        // object_sub_ = this->create_subscription<rplidar_ros::msg::ObjectInfoArray>(
        //     "/obstacle_info", 1,
        //     std::bind(&LaneDetectionNode::object_callback, this, std::placeholders::_1));

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

        // 초기값
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
            cv::Mat birdview_color;
            cv::cvtColor(birdview_gray, birdview_color, cv::COLOR_GRAY2BGR);
            cv::warpPerspective(yellow_mask, yellow_warp, warp_matrix_, yellow_mask.size(), cv::INTER_NEAREST);

            int window_height = 40, margin = 40, minpix = 10, num_windows = 6;
            int width = birdview_gray.cols, height = birdview_gray.rows;
            float alpha = 1.2f;  // momentum 계수

            int left_sum_x = 0, left_count_px = 0, right_sum_x = 0, right_count_px = 0;
            for (int y = 0; y < height; ++y) {
                const uchar* row_ptr = birdview_gray.ptr<uchar>(y);
                for (int x = 0; x < width; ++x) {
                    if (row_ptr[x] > 0) {
                        if (x < width / 2) {
                            left_sum_x += x;
                            left_count_px++;
                        } else {
                            right_sum_x += x;
                            right_count_px++;
                        }
                    }
                }
            }
            int left_x = (left_count_px > 0) ? (left_sum_x / left_count_px) : 80;
            int right_x = (right_count_px > 0) ? (right_sum_x / right_count_px) : 240;

            int prev_left_x = left_x;
            int prev_right_x = right_x;

            std::vector<int> left_centers, right_centers;
            // int white_left = 0, yellow_left = 0, white_right = 0, yellow_right = 0;

            for (int i = 0; i < num_windows; ++i) {
                int y_low = height - (i + 1) * window_height;
                int y_high = height - i * window_height;
                int lx_low = std::max(0, left_x - margin), lx_high = std::min(width, left_x + margin);
                int rx_low = std::max(0, right_x - margin), rx_high = std::min(width, right_x + margin);
                cv::Rect left_win(lx_low, y_low, lx_high - lx_low, y_high - y_low);
                cv::Rect right_win(rx_low, y_low, rx_high - rx_low, y_high - y_low);

                // white_left  += cv::countNonZero(white_mask(left_win));
                // yellow_left += cv::countNonZero(yellow_mask(left_win));
                // white_right  += cv::countNonZero(white_mask(right_win));
                // yellow_right += cv::countNonZero(yellow_mask(right_win));

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
                    int current_left_x = lx_low + lx_sum / lx_count;
                    int delta = current_left_x - prev_left_x;
                    left_x = current_left_x + static_cast<int>(alpha * delta);
                    prev_left_x = current_left_x;
                    left_centers.push_back(left_x);
                }

                for (int row = 0; row < right_win.height; ++row) {
                    const uchar* ptr = birdview_gray.ptr<uchar>(y_low + row) + rx_low;
                    for (int col = 0; col < rx_high - rx_low; ++col) {
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

            int yellow_left = 0, yellow_right = 0;
            for (int y = height / 2; y < height; ++y) {
                const uchar* row_ptr = yellow_warp.ptr<uchar>(y);
                for (int x = 0; x < width / 2; ++x) {
                    if (row_ptr[x] > 0) yellow_left++;
                }
                for (int x = width / 2; x < width; ++x) {
                    if (row_ptr[x] > 0) yellow_right++;
                }
            }


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

            double left_ratio = static_cast<double>(left_count_hist) / lane_history_.size();
            double right_ratio = static_cast<double>(right_count_hist) / lane_history_.size();
            double unknown_ratio = 1.0 - left_ratio - right_ratio;

            std_msgs::msg::String log_msg;
            std::stringstream ss;
            ss << "Lane: " << current_lane_
               << " | left=" << left_ratio
               << " right=" << right_ratio
               << " unknown=" << unknown_ratio
               << " | is_avoiding: " << is_avoiding_;
            log_msg.data = ss.str();
            log_pub_->publish(log_msg);

            auto elapsed = this->now() - start_time_;
            if (elapsed.seconds() > 10.0 && elapsed.seconds() <= 20.0) {
                if (current_lane_ == "unknown")
                    unknown_count_++;
            }

            if (elapsed.seconds() > 20.0 && !counted_window_) {
                counted_window_ = true;
                RCLCPP_INFO(this->get_logger(), "[Unknown Count] Between 10-20s: %d", unknown_count_);
            }

            int mid_x;
            size_t idx = 3;
            if (left_centers.size() > idx && right_centers.size() > idx)
                mid_x = (left_centers[idx] + right_centers[idx]) / 2;
            else if (left_centers.size() > idx)
                mid_x = left_centers[idx] + 90;
            else if (right_centers.size() > idx)
                mid_x = right_centers[idx] - 90;
            else
                mid_x = prev_mid_x_;  // 이전 mid_x 유지

            int mid_y = height - (idx + 0.5) * window_height;
            cv::circle(birdview_color, cv::Point(mid_x, mid_y), 5, cv::Scalar(0, 0, 255), -1);

            double error = mid_x - (width / 2.0);
            double error_normalized = error / (width / 2.0);
            double max_angle = 1.3;
            double k = 2.0;
            double angle;
            if (mid_x == prev_mid_x_) {
                angle = prev_angle_;  // 이전 angle 유지
            } else {
                angle = max_angle * (1 - std::exp(-k * std::abs(error_normalized))) * (error_normalized >= 0 ? 1 : -1);
                prev_mid_x_ = mid_x;
                prev_angle_ = angle;
            }

            if (!is_avoiding_ || (this->now() - avoid_start_time_) >= avoid_duration_) {
                is_avoiding_ = false;
                motor_control::msg::ServoCtrlMsg msg;
                msg.angle = angle;
                msg.throttle = 0.56;
                servo_pub_->publish(msg);
            }

            cv::imshow("Binary with Windows", birdview_color);
            cv::waitKey(1);

        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception: %s", e.what());
        }
    }

   

    // void laser_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
    //     if (is_avoiding_) return;

    //     bool found = false;

    //     for (size_t i = 0; i < msg->ranges.size(); ++i) {
    //         float angle = msg->angle_min + i * msg->angle_increment;
    //         float r = msg->ranges[i];

    //         if (std::isnan(r) || std::isinf(r)) continue;

    //         // polar → cartesian (부호 반전)
    //         float x = -(r * cos(angle));
    //         float y = -(r * sin(angle));

    //         if (x > 0.1 && x < 0.8 && std::abs(y) < 0.2) {
    //             found = true;
    //             // RCLCPP_INFO(this->get_logger(), "[LaserScan Obstacle] Point at x=%.2f, y=%.2f", x, y);
    //             break;  // 하나라도 발견되면 바로 탈출
    //         }
    //     }

    //     if (found) {
    //         motor_control::msg::ServoCtrlMsg avoid;
    //         avoid.throttle = 0.53;

    //         if (current_lane_ == "left_lane") {
    //             avoid.angle = 1.0;  // 우측 회피
    //         } else if (current_lane_ == "right_lane") {
    //             avoid.angle = -1.0; // 좌측 회피
    //         } else {
    //             avoid.angle = 0.0;
    //         }

    //         last_avoid_angle_ = avoid.angle;
    //         servo_pub_->publish(avoid);
    //         is_avoiding_ = true;
    //         avoid_start_time_ = this->now();
    //     }
    // }
    void laser_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
        if (is_avoiding_) {
            auto elapsed = this->now() - avoid_start_time_;
            auto remaining = avoid_duration_ - elapsed;

            if (remaining.seconds() <= 0.1 && remaining.seconds() > 0.0) {
                motor_control::msg::ServoCtrlMsg reverse_msg;
                reverse_msg.throttle = 0.53;

                if (last_avoid_angle_ > 0)
                    reverse_msg.angle = -0.7;
                else if (last_avoid_angle_ < 0)
                    reverse_msg.angle = 0.7;
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
    // rclcpp::Subscription<rplidar_ros::msg::ObjectInfoArray>::SharedPtr object_sub_;
    rclcpp::Publisher<motor_control::msg::ServoCtrlMsg>::SharedPtr servo_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr log_pub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;

    std::string current_lane_ = "unknown";
    bool is_avoiding_ = false;
    rclcpp::Time avoid_start_time_;
    const rclcpp::Duration avoid_duration_ = rclcpp::Duration::from_seconds(0.4);
    double last_avoid_angle_ = 0.0;

    std::deque<std::string> lane_history_;
    const size_t lane_history_size_ = 10;
    const double trust_threshold_ = 0.6;

    int unknown_count_ = 0;
    bool counted_window_ = false;
    
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
