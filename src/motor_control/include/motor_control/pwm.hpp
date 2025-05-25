#ifndef PWM_HPP
#define PWM_HPP

#include <string>
#include "rclcpp/rclcpp.hpp"

namespace PWM {

class Servo {
public:
    Servo(int channel, rclcpp::Logger logger);
    void setPeriod(int period_ns);
    void setDuty(int duty_ns);

private:
    int channel_;
    std::string syspath_;
    rclcpp::Logger logger_;
};

}  // namespace PWM

#endif
