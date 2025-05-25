// class DeepracerNode : public rclcpp::Node
// {
// public:
//     DeepracerNode()
//     : Node("deepracer_node")
//     {
//         publisher_ = this->create_publisher<motor_control::msg::ServoCtrlMsg>("/servo_cmd", 10);
//         timer_ = this->create_wall_timer(
//             std::chrono::milliseconds(20),
//             std::bind(&DeepracerNode::publish_msg, this)
//         );
//     }

// private:
//     void publish_msg()
//     {
//         auto msg = motor_control::msg::ServoCtrlMsg();
//         msg.angle = 0;      // Example value for angle
//         msg.throttle = 0;   // Example value for throttle
//         RCLCPP_INFO(this->get_logger(), "Publishing: angle=%f, throttle=%f", msg.angle, msg.throttle);
//         publisher_->publish(msg);
//     }

//     rclcpp::Publisher<motor_control::msg::ServoCtrlMsg>::SharedPtr publisher_;
//     rclcpp::TimerBase::SharedPtr timer_;
// };

// int main(int argc, char ** argv)
// {
//     rclcpp::init(argc, argv);
//     rclcpp::spin(std::make_shared<DeepracerNode>());
//     rclcpp::shutdown();
//     return 0;
// }

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "motor_control/msg/servo_ctrl_msg.hpp"

class DeepracerNode : public rclcpp::Node
{
public:
    DeepracerNode()
    : Node("deepracer_node")
    {
        publisher_ = this->create_publisher<motor_control::msg::ServoCtrlMsg>("/servo_cmd", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(20),  // 1초마다 실행
            std::bind(&DeepracerNode::publish_msg, this)
        );
    }

private:
    void publish_msg()
    {
        auto msg = motor_control::msg::ServoCtrlMsg();
        angle_ = 0.5;
        throttle_ = 0.5;
        msg.angle = angle_;      // 현재 angle 값
        msg.throttle = throttle_; 
         
        // 현재 throttle 값

        // angle 값 감소 (최소 -20)
        if (angle_ > -20) {
            angle_ -= 0.01;  // angle 값 1씩 감소
        }

        // throttle 값 감소 (최소 0)
        if (throttle_ > 0) {
            throttle_ -= 0.01;  // throttle 값 1씩 감소
        }

        // 로그로 값 출력
        RCLCPP_INFO(this->get_logger(), "Publishing: angle=%f, throttle=%f", msg.angle, msg.throttle);

        // 메시지 퍼블리시
        publisher_->publish(msg);
    }

    rclcpp::Publisher<motor_control::msg::ServoCtrlMsg>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    // angle과 throttle 값을 추적하는 멤버 변수
    double angle_;
    double throttle_;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DeepracerNode>());
    rclcpp::shutdown();
    return 0;
}
