// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rplidar_ros:msg/ObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__STRUCT_HPP_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__rplidar_ros__msg__ObjectInfo __attribute__((deprecated))
#else
# define DEPRECATED__rplidar_ros__msg__ObjectInfo __declspec(deprecated)
#endif

namespace rplidar_ros
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ObjectInfo_
{
  using Type = ObjectInfo_<ContainerAllocator>;

  explicit ObjectInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0f;
      this->y = 0.0f;
      this->distance = 0.0f;
    }
  }

  explicit ObjectInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0f;
      this->y = 0.0f;
      this->distance = 0.0f;
    }
  }

  // field types and members
  using _x_type =
    float;
  _x_type x;
  using _y_type =
    float;
  _y_type y;
  using _distance_type =
    float;
  _distance_type distance;

  // setters for named parameter idiom
  Type & set__x(
    const float & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const float & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__distance(
    const float & _arg)
  {
    this->distance = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rplidar_ros::msg::ObjectInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const rplidar_ros::msg::ObjectInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rplidar_ros::msg::ObjectInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rplidar_ros::msg::ObjectInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rplidar_ros::msg::ObjectInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rplidar_ros::msg::ObjectInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rplidar_ros::msg::ObjectInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rplidar_ros::msg::ObjectInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rplidar_ros::msg::ObjectInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rplidar_ros::msg::ObjectInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rplidar_ros__msg__ObjectInfo
    std::shared_ptr<rplidar_ros::msg::ObjectInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rplidar_ros__msg__ObjectInfo
    std::shared_ptr<rplidar_ros::msg::ObjectInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ObjectInfo_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->distance != other.distance) {
      return false;
    }
    return true;
  }
  bool operator!=(const ObjectInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ObjectInfo_

// alias to use template instance with default allocator
using ObjectInfo =
  rplidar_ros::msg::ObjectInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rplidar_ros

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO__STRUCT_HPP_
