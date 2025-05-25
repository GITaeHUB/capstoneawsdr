// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__BUILDER_HPP_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__BUILDER_HPP_

#include "rplidar_ros/msg/detail/object_info_array__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace rplidar_ros
{

namespace msg
{

namespace builder
{

class Init_ObjectInfoArray_objects
{
public:
  explicit Init_ObjectInfoArray_objects(::rplidar_ros::msg::ObjectInfoArray & msg)
  : msg_(msg)
  {}
  ::rplidar_ros::msg::ObjectInfoArray objects(::rplidar_ros::msg::ObjectInfoArray::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rplidar_ros::msg::ObjectInfoArray msg_;
};

class Init_ObjectInfoArray_header
{
public:
  Init_ObjectInfoArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectInfoArray_objects header(::rplidar_ros::msg::ObjectInfoArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ObjectInfoArray_objects(msg_);
  }

private:
  ::rplidar_ros::msg::ObjectInfoArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rplidar_ros::msg::ObjectInfoArray>()
{
  return rplidar_ros::msg::builder::Init_ObjectInfoArray_header();
}

}  // namespace rplidar_ros

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__BUILDER_HPP_
