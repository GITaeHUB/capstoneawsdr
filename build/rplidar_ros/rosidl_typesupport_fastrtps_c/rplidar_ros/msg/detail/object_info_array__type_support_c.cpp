// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice
#include "rplidar_ros/msg/detail/object_info_array__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rplidar_ros/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rplidar_ros/msg/detail/object_info_array__struct.h"
#include "rplidar_ros/msg/detail/object_info_array__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rplidar_ros/msg/detail/object_info__functions.h"  // objects
#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
size_t get_serialized_size_rplidar_ros__msg__ObjectInfo(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_rplidar_ros__msg__ObjectInfo(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rplidar_ros, msg, ObjectInfo)();
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rplidar_ros
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rplidar_ros
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rplidar_ros
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _ObjectInfoArray__ros_msg_type = rplidar_ros__msg__ObjectInfoArray;

static bool _ObjectInfoArray__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ObjectInfoArray__ros_msg_type * ros_message = static_cast<const _ObjectInfoArray__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: objects
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, rplidar_ros, msg, ObjectInfo
      )()->data);
    size_t size = ros_message->objects.size;
    auto array_ptr = ros_message->objects.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  return true;
}

static bool _ObjectInfoArray__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ObjectInfoArray__ros_msg_type * ros_message = static_cast<_ObjectInfoArray__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: objects
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, rplidar_ros, msg, ObjectInfo
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->objects.data) {
      rplidar_ros__msg__ObjectInfo__Sequence__fini(&ros_message->objects);
    }
    if (!rplidar_ros__msg__ObjectInfo__Sequence__init(&ros_message->objects, size)) {
      return "failed to create array for field 'objects'";
    }
    auto array_ptr = ros_message->objects.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rplidar_ros
size_t get_serialized_size_rplidar_ros__msg__ObjectInfoArray(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ObjectInfoArray__ros_msg_type * ros_message = static_cast<const _ObjectInfoArray__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name objects
  {
    size_t array_size = ros_message->objects.size;
    auto array_ptr = ros_message->objects.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_rplidar_ros__msg__ObjectInfo(
        &array_ptr[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ObjectInfoArray__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_rplidar_ros__msg__ObjectInfoArray(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rplidar_ros
size_t max_serialized_size_rplidar_ros__msg__ObjectInfoArray(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_std_msgs__msg__Header(
        full_bounded, current_alignment);
    }
  }
  // member: objects
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_rplidar_ros__msg__ObjectInfo(
        full_bounded, current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _ObjectInfoArray__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_rplidar_ros__msg__ObjectInfoArray(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_ObjectInfoArray = {
  "rplidar_ros::msg",
  "ObjectInfoArray",
  _ObjectInfoArray__cdr_serialize,
  _ObjectInfoArray__cdr_deserialize,
  _ObjectInfoArray__get_serialized_size,
  _ObjectInfoArray__max_serialized_size
};

static rosidl_message_type_support_t _ObjectInfoArray__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ObjectInfoArray,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rplidar_ros, msg, ObjectInfoArray)() {
  return &_ObjectInfoArray__type_support;
}

#if defined(__cplusplus)
}
#endif
