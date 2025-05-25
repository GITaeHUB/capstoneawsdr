// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_control:msg/ServoCtrlMsg.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__SERVO_CTRL_MSG__BUILDER_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__SERVO_CTRL_MSG__BUILDER_HPP_

#include "motor_control/msg/detail/servo_ctrl_msg__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace motor_control
{

namespace msg
{

namespace builder
{

class Init_ServoCtrlMsg_throttle
{
public:
  explicit Init_ServoCtrlMsg_throttle(::motor_control::msg::ServoCtrlMsg & msg)
  : msg_(msg)
  {}
  ::motor_control::msg::ServoCtrlMsg throttle(::motor_control::msg::ServoCtrlMsg::_throttle_type arg)
  {
    msg_.throttle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_control::msg::ServoCtrlMsg msg_;
};

class Init_ServoCtrlMsg_angle
{
public:
  Init_ServoCtrlMsg_angle()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoCtrlMsg_throttle angle(::motor_control::msg::ServoCtrlMsg::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_ServoCtrlMsg_throttle(msg_);
  }

private:
  ::motor_control::msg::ServoCtrlMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_control::msg::ServoCtrlMsg>()
{
  return motor_control::msg::builder::Init_ServoCtrlMsg_angle();
}

}  // namespace motor_control

#endif  // MOTOR_CONTROL__MSG__DETAIL__SERVO_CTRL_MSG__BUILDER_HPP_
