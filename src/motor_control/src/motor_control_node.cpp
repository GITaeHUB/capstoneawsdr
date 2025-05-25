#include "rclcpp/rclcpp.hpp"
#include "motor_control/pwm.hpp"
#include "motor_control/msg/servo_ctrl_msg.hpp"

#include <fstream>

using std::placeholders::_1;

class MotorControlNode : public rclcpp::Node {
public:
    MotorControlNode() : Node("motor_control_node") {
        steering_ = std::make_shared<PWM::Servo>(1, this->get_logger());
        throttle_ = std::make_shared<PWM::Servo>(0, this->get_logger());

        int period = 20000000; // 20ms = 50Hz  20000000
        steering_->setPeriod(period);
        throttle_->setPeriod(period);

        sub_ = this->create_subscription<motor_control::msg::ServoCtrlMsg>(
            "/servo_cmd", 1, std::bind(&MotorControlNode::callback, this, _1));
    }

private:

    void callback(const motor_control::msg::ServoCtrlMsg::SharedPtr msg) {
        int steer_pwm = 1450000 - static_cast<int>(msg->angle * 250000);
        int throttle_pwm = 1500000 - static_cast<int>(msg->throttle * 150000);
        // throttle_pwm += (rand() % 2) * 10;

        steering_->setDuty(steer_pwm);
        throttle_->setDuty(throttle_pwm);
    }

    std::shared_ptr<PWM::Servo> steering_;
    std::shared_ptr<PWM::Servo> throttle_;
    rclcpp::Subscription<motor_control::msg::ServoCtrlMsg>::SharedPtr sub_;

};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MotorControlNode>());
    rclcpp::shutdown();
    return 0;
}