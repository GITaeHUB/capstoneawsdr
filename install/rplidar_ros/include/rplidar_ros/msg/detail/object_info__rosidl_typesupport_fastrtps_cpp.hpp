// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from rplidar_ros:msg/ObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "rplidar_ros/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "rplidar_ros/msg/detail/object_info__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace rplidar_ros
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
cdr_serialize(
  const rplidar_ros::msg::ObjectInfo & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  rplidar_ros::msg::ObjectInfo & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
get_serialized_size(
  const rplidar_ros::msg::ObjectInfo & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
max_serialized_size_ObjectInfo(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace rplidar_ros

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, rplidar_ros, msg, ObjectInfo)();

#ifdef __cplusplus
}
#endif

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
