// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from rplidar_ros:msg/ObjectInfo.idl
// generated code does not contain a copyright notice
#include "rplidar_ros/msg/detail/object_info__rosidl_typesupport_fastrtps_cpp.hpp"
#include "rplidar_ros/msg/detail/object_info__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

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
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: x
  cdr << ros_message.x;
  // Member: y
  cdr << ros_message.y;
  // Member: distance
  cdr << ros_message.distance;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  rplidar_ros::msg::ObjectInfo & ros_message)
{
  // Member: x
  cdr >> ros_message.x;

  // Member: y
  cdr >> ros_message.y;

  // Member: distance
  cdr >> ros_message.distance;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
get_serialized_size(
  const rplidar_ros::msg::ObjectInfo & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: x
  {
    size_t item_size = sizeof(ros_message.x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: y
  {
    size_t item_size = sizeof(ros_message.y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: distance
  {
    size_t item_size = sizeof(ros_message.distance);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
max_serialized_size_ObjectInfo(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: x
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: y
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: distance
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  return current_alignment - initial_alignment;
}

static bool _ObjectInfo__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const rplidar_ros::msg::ObjectInfo *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ObjectInfo__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<rplidar_ros::msg::ObjectInfo *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ObjectInfo__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const rplidar_ros::msg::ObjectInfo *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ObjectInfo__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ObjectInfo(full_bounded, 0);
}

static message_type_support_callbacks_t _ObjectInfo__callbacks = {
  "rplidar_ros::msg",
  "ObjectInfo",
  _ObjectInfo__cdr_serialize,
  _ObjectInfo__cdr_deserialize,
  _ObjectInfo__get_serialized_size,
  _ObjectInfo__max_serialized_size
};

static rosidl_message_type_support_t _ObjectInfo__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ObjectInfo__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace rplidar_ros

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_rplidar_ros
const rosidl_message_type_support_t *
get_message_type_support_handle<rplidar_ros::msg::ObjectInfo>()
{
  return &rplidar_ros::msg::typesupport_fastrtps_cpp::_ObjectInfo__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, rplidar_ros, msg, ObjectInfo)() {
  return &rplidar_ros::msg::typesupport_fastrtps_cpp::_ObjectInfo__handle;
}

#ifdef __cplusplus
}
#endif
