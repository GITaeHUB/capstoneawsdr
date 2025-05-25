// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__STRUCT_HPP_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'objects'
#include "rplidar_ros/msg/detail/object_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rplidar_ros__msg__ObjectInfoArray __attribute__((deprecated))
#else
# define DEPRECATED__rplidar_ros__msg__ObjectInfoArray __declspec(deprecated)
#endif

namespace rplidar_ros
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ObjectInfoArray_
{
  using Type = ObjectInfoArray_<ContainerAllocator>;

  explicit ObjectInfoArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit ObjectInfoArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _objects_type =
    std::vector<rplidar_ros::msg::ObjectInfo_<ContainerAllocator>, typename ContainerAllocator::template rebind<rplidar_ros::msg::ObjectInfo_<ContainerAllocator>>::other>;
  _objects_type objects;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__objects(
    const std::vector<rplidar_ros::msg::ObjectInfo_<ContainerAllocator>, typename ContainerAllocator::template rebind<rplidar_ros::msg::ObjectInfo_<ContainerAllocator>>::other> & _arg)
  {
    this->objects = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rplidar_ros__msg__ObjectInfoArray
    std::shared_ptr<rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rplidar_ros__msg__ObjectInfoArray
    std::shared_ptr<rplidar_ros::msg::ObjectInfoArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ObjectInfoArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->objects != other.objects) {
      return false;
    }
    return true;
  }
  bool operator!=(const ObjectInfoArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ObjectInfoArray_

// alias to use template instance with default allocator
using ObjectInfoArray =
  rplidar_ros::msg::ObjectInfoArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rplidar_ros

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__STRUCT_HPP_
