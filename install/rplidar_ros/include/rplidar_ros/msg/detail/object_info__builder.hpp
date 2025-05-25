// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rplidar_ros:msg/ObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__BUILDER_HPP_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__BUILDER_HPP_

#include "rplidar_ros/msg/detail/object_info__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace rplidar_ros
{

namespace msg
{

namespace builder
{

class Init_ObjectInfo_distance
{
public:
  explicit Init_ObjectInfo_distance(::rplidar_ros::msg::ObjectInfo & msg)
  : msg_(msg)
  {}
  ::rplidar_ros::msg::ObjectInfo distance(::rplidar_ros::msg::ObjectInfo::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rplidar_ros::msg::ObjectInfo msg_;
};

class Init_ObjectInfo_y
{
public:
  explicit Init_ObjectInfo_y(::rplidar_ros::msg::ObjectInfo & msg)
  : msg_(msg)
  {}
  Init_ObjectInfo_distance y(::rplidar_ros::msg::ObjectInfo::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_ObjectInfo_distance(msg_);
  }

private:
  ::rplidar_ros::msg::ObjectInfo msg_;
};

class Init_ObjectInfo_x
{
public:
  Init_ObjectInfo_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectInfo_y x(::rplidar_ros::msg::ObjectInfo::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_ObjectInfo_y(msg_);
  }

private:
  ::rplidar_ros::msg::ObjectInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rplidar_ros::msg::ObjectInfo>()
{
  return rplidar_ros::msg::builder::Init_ObjectInfo_x();
}

}  // namespace rplidar_ros

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__BUILDER_HPP_
