// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rplidar_ros/msg/detail/object_info_array__rosidl_typesupport_introspection_c.h"
#include "rplidar_ros/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rplidar_ros/msg/detail/object_info_array__functions.h"
#include "rplidar_ros/msg/detail/object_info_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `objects`
#include "rplidar_ros/msg/object_info.h"
// Member `objects`
#include "rplidar_ros/msg/detail/object_info__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rplidar_ros__msg__ObjectInfoArray__init(message_memory);
}

void ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_fini_function(void * message_memory)
{
  rplidar_ros__msg__ObjectInfoArray__fini(message_memory);
}

size_t ObjectInfoArray__rosidl_typesupport_introspection_c__size_function__ObjectInfo__objects(
  const void * untyped_member)
{
  const rplidar_ros__msg__ObjectInfo__Sequence * member =
    (const rplidar_ros__msg__ObjectInfo__Sequence *)(untyped_member);
  return member->size;
}

const void * ObjectInfoArray__rosidl_typesupport_introspection_c__get_const_function__ObjectInfo__objects(
  const void * untyped_member, size_t index)
{
  const rplidar_ros__msg__ObjectInfo__Sequence * member =
    (const rplidar_ros__msg__ObjectInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void * ObjectInfoArray__rosidl_typesupport_introspection_c__get_function__ObjectInfo__objects(
  void * untyped_member, size_t index)
{
  rplidar_ros__msg__ObjectInfo__Sequence * member =
    (rplidar_ros__msg__ObjectInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

bool ObjectInfoArray__rosidl_typesupport_introspection_c__resize_function__ObjectInfo__objects(
  void * untyped_member, size_t size)
{
  rplidar_ros__msg__ObjectInfo__Sequence * member =
    (rplidar_ros__msg__ObjectInfo__Sequence *)(untyped_member);
  rplidar_ros__msg__ObjectInfo__Sequence__fini(member);
  return rplidar_ros__msg__ObjectInfo__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rplidar_ros__msg__ObjectInfoArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rplidar_ros__msg__ObjectInfoArray, objects),  // bytes offset in struct
    NULL,  // default value
    ObjectInfoArray__rosidl_typesupport_introspection_c__size_function__ObjectInfo__objects,  // size() function pointer
    ObjectInfoArray__rosidl_typesupport_introspection_c__get_const_function__ObjectInfo__objects,  // get_const(index) function pointer
    ObjectInfoArray__rosidl_typesupport_introspection_c__get_function__ObjectInfo__objects,  // get(index) function pointer
    ObjectInfoArray__rosidl_typesupport_introspection_c__resize_function__ObjectInfo__objects  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_members = {
  "rplidar_ros__msg",  // message namespace
  "ObjectInfoArray",  // message name
  2,  // number of fields
  sizeof(rplidar_ros__msg__ObjectInfoArray),
  ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_member_array,  // message members
  ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_init_function,  // function to initialize message memory (memory has to be allocated)
  ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_type_support_handle = {
  0,
  &ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rplidar_ros
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rplidar_ros, msg, ObjectInfoArray)() {
  ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rplidar_ros, msg, ObjectInfo)();
  if (!ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_type_support_handle.typesupport_identifier) {
    ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ObjectInfoArray__rosidl_typesupport_introspection_c__ObjectInfoArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
