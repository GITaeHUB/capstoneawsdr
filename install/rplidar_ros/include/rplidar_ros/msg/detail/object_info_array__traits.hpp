// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__TRAITS_HPP_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__TRAITS_HPP_

#include "rplidar_ros/msg/detail/object_info_array__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rplidar_ros::msg::ObjectInfoArray>()
{
  return "rplidar_ros::msg::ObjectInfoArray";
}

template<>
inline const char * name<rplidar_ros::msg::ObjectInfoArray>()
{
  return "rplidar_ros/msg/ObjectInfoArray";
}

template<>
struct has_fixed_size<rplidar_ros::msg::ObjectInfoArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rplidar_ros::msg::ObjectInfoArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rplidar_ros::msg::ObjectInfoArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__TRAITS_HPP_
