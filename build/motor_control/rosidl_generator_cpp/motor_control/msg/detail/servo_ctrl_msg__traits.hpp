// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_control:msg/ServoCtrlMsg.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__SERVO_CTRL_MSG__TRAITS_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__SERVO_CTRL_MSG__TRAITS_HPP_

#include "motor_control/msg/detail/servo_ctrl_msg__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<motor_control::msg::ServoCtrlMsg>()
{
  return "motor_control::msg::ServoCtrlMsg";
}

template<>
inline const char * name<motor_control::msg::ServoCtrlMsg>()
{
  return "motor_control/msg/ServoCtrlMsg";
}

template<>
struct has_fixed_size<motor_control::msg::ServoCtrlMsg>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<motor_control::msg::ServoCtrlMsg>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<motor_control::msg::ServoCtrlMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_CONTROL__MSG__DETAIL__SERVO_CTRL_MSG__TRAITS_HPP_
