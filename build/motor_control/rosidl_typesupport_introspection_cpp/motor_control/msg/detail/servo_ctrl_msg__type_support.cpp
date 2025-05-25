// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from motor_control:msg/ServoCtrlMsg.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "motor_control/msg/detail/servo_ctrl_msg__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace motor_control
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ServoCtrlMsg_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) motor_control::msg::ServoCtrlMsg(_init);
}

void ServoCtrlMsg_fini_function(void * message_memory)
{
  auto typed_message = static_cast<motor_control::msg::ServoCtrlMsg *>(message_memory);
  typed_message->~ServoCtrlMsg();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ServoCtrlMsg_message_member_array[2] = {
  {
    "angle",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_control::msg::ServoCtrlMsg, angle),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "throttle",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_control::msg::ServoCtrlMsg, throttle),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ServoCtrlMsg_message_members = {
  "motor_control::msg",  // message namespace
  "ServoCtrlMsg",  // message name
  2,  // number of fields
  sizeof(motor_control::msg::ServoCtrlMsg),
  ServoCtrlMsg_message_member_array,  // message members
  ServoCtrlMsg_init_function,  // function to initialize message memory (memory has to be allocated)
  ServoCtrlMsg_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ServoCtrlMsg_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ServoCtrlMsg_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace motor_control


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<motor_control::msg::ServoCtrlMsg>()
{
  return &::motor_control::msg::rosidl_typesupport_introspection_cpp::ServoCtrlMsg_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, motor_control, msg, ServoCtrlMsg)() {
  return &::motor_control::msg::rosidl_typesupport_introspection_cpp::ServoCtrlMsg_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
