// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice
#include "rplidar_ros/msg/detail/object_info_array__rosidl_typesupport_fastrtps_cpp.hpp"
#include "rplidar_ros/msg/detail/object_info_array__struct.hpp"

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
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs

namespace rplidar_ros
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const rplidar_ros::msg::ObjectInfo &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  rplidar_ros::msg::ObjectInfo &);
size_t get_serialized_size(
  const rplidar_ros::msg::ObjectInfo &,
  size_t current_alignment);
size_t
max_serialized_size_ObjectInfo(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace rplidar_ros


namespace rplidar_ros
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
cdr_serialize(
  const rplidar_ros::msg::ObjectInfoArray & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);
  // Member: objects
  {
    size_t size = ros_message.objects.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      rplidar_ros::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.objects[i],
        cdr);
    }
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  rplidar_ros::msg::ObjectInfoArray & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: objects
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.objects.resize(size);
    for (size_t i = 0; i < size; i++) {
      rplidar_ros::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.objects[i]);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
get_serialized_size(
  const rplidar_ros::msg::ObjectInfoArray & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header

  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);
  // Member: objects
  {
    size_t array_size = ros_message.objects.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        rplidar_ros::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.objects[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rplidar_ros
max_serialized_size_ObjectInfoArray(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        full_bounded, current_alignment);
    }
  }

  // Member: objects
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        rplidar_ros::msg::typesupport_fastrtps_cpp::max_serialized_size_ObjectInfo(
        full_bounded, current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static bool _ObjectInfoArray__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const rplidar_ros::msg::ObjectInfoArray *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ObjectInfoArray__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<rplidar_ros::msg::ObjectInfoArray *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ObjectInfoArray__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const rplidar_ros::msg::ObjectInfoArray *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ObjectInfoArray__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ObjectInfoArray(full_bounded, 0);
}

static message_type_support_callbacks_t _ObjectInfoArray__callbacks = {
  "rplidar_ros::msg",
  "ObjectInfoArray",
  _ObjectInfoArray__cdr_serialize,
  _ObjectInfoArray__cdr_deserialize,
  _ObjectInfoArray__get_serialized_size,
  _ObjectInfoArray__max_serialized_size
};

static rosidl_message_type_support_t _ObjectInfoArray__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ObjectInfoArray__callbacks,
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
get_message_type_support_handle<rplidar_ros::msg::ObjectInfoArray>()
{
  return &rplidar_ros::msg::typesupport_fastrtps_cpp::_ObjectInfoArray__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, rplidar_ros, msg, ObjectInfoArray)() {
  return &rplidar_ros::msg::typesupport_fastrtps_cpp::_ObjectInfoArray__handle;
}

#ifdef __cplusplus
}
#endif
