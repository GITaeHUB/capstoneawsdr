// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rplidar_ros:msg/ObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__TRAITS_HPP_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__TRAITS_HPP_

#include "rplidar_ros/msg/detail/object_info__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rplidar_ros::msg::ObjectInfo>()
{
  return "rplidar_ros::msg::ObjectInfo";
}

template<>
inline const char * name<rplidar_ros::msg::ObjectInfo>()
{
  return "rplidar_ros/msg/ObjectInfo";
}

template<>
struct has_fixed_size<rplidar_ros::msg::ObjectInfo>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rplidar_ros::msg::ObjectInfo>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rplidar_ros::msg::ObjectInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__TRAITS_HPP_
