// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__STRUCT_H_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'objects'
#include "rplidar_ros/msg/detail/object_info__struct.h"

// Struct defined in msg/ObjectInfoArray in the package rplidar_ros.
typedef struct rplidar_ros__msg__ObjectInfoArray
{
  std_msgs__msg__Header header;
  rplidar_ros__msg__ObjectInfo__Sequence objects;
} rplidar_ros__msg__ObjectInfoArray;

// Struct for a sequence of rplidar_ros__msg__ObjectInfoArray.
typedef struct rplidar_ros__msg__ObjectInfoArray__Sequence
{
  rplidar_ros__msg__ObjectInfoArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rplidar_ros__msg__ObjectInfoArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__STRUCT_H_
