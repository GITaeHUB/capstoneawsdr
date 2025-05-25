// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rplidar_ros:msg/ObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__STRUCT_H_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/ObjectInfo in the package rplidar_ros.
typedef struct rplidar_ros__msg__ObjectInfo
{
  float x;
  float y;
  float distance;
} rplidar_ros__msg__ObjectInfo;

// Struct for a sequence of rplidar_ros__msg__ObjectInfo.
typedef struct rplidar_ros__msg__ObjectInfo__Sequence
{
  rplidar_ros__msg__ObjectInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rplidar_ros__msg__ObjectInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__STRUCT_H_
