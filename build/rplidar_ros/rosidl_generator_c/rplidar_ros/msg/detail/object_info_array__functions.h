// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice

#ifndef RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__FUNCTIONS_H_
#define RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "rplidar_ros/msg/rosidl_generator_c__visibility_control.h"

#include "rplidar_ros/msg/detail/object_info_array__struct.h"

/// Initialize msg/ObjectInfoArray message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * rplidar_ros__msg__ObjectInfoArray
 * )) before or use
 * rplidar_ros__msg__ObjectInfoArray__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_rplidar_ros
bool
rplidar_ros__msg__ObjectInfoArray__init(rplidar_ros__msg__ObjectInfoArray * msg);

/// Finalize msg/ObjectInfoArray message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rplidar_ros
void
rplidar_ros__msg__ObjectInfoArray__fini(rplidar_ros__msg__ObjectInfoArray * msg);

/// Create msg/ObjectInfoArray message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * rplidar_ros__msg__ObjectInfoArray__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rplidar_ros
rplidar_ros__msg__ObjectInfoArray *
rplidar_ros__msg__ObjectInfoArray__create();

/// Destroy msg/ObjectInfoArray message.
/**
 * It calls
 * rplidar_ros__msg__ObjectInfoArray__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rplidar_ros
void
rplidar_ros__msg__ObjectInfoArray__destroy(rplidar_ros__msg__ObjectInfoArray * msg);


/// Initialize array of msg/ObjectInfoArray messages.
/**
 * It allocates the memory for the number of elements and calls
 * rplidar_ros__msg__ObjectInfoArray__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_rplidar_ros
bool
rplidar_ros__msg__ObjectInfoArray__Sequence__init(rplidar_ros__msg__ObjectInfoArray__Sequence * array, size_t size);

/// Finalize array of msg/ObjectInfoArray messages.
/**
 * It calls
 * rplidar_ros__msg__ObjectInfoArray__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rplidar_ros
void
rplidar_ros__msg__ObjectInfoArray__Sequence__fini(rplidar_ros__msg__ObjectInfoArray__Sequence * array);

/// Create array of msg/ObjectInfoArray messages.
/**
 * It allocates the memory for the array and calls
 * rplidar_ros__msg__ObjectInfoArray__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rplidar_ros
rplidar_ros__msg__ObjectInfoArray__Sequence *
rplidar_ros__msg__ObjectInfoArray__Sequence__create(size_t size);

/// Destroy array of msg/ObjectInfoArray messages.
/**
 * It calls
 * rplidar_ros__msg__ObjectInfoArray__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rplidar_ros
void
rplidar_ros__msg__ObjectInfoArray__Sequence__destroy(rplidar_ros__msg__ObjectInfoArray__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RPLIDAR_ROS__MSG__DETAIL__OBJECT_INFO_ARRAY__FUNCTIONS_H_
