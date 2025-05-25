// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rplidar_ros:msg/ObjectInfoArray.idl
// generated code does not contain a copyright notice
#include "rplidar_ros/msg/detail/object_info_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `objects`
#include "rplidar_ros/msg/detail/object_info__functions.h"

bool
rplidar_ros__msg__ObjectInfoArray__init(rplidar_ros__msg__ObjectInfoArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    rplidar_ros__msg__ObjectInfoArray__fini(msg);
    return false;
  }
  // objects
  if (!rplidar_ros__msg__ObjectInfo__Sequence__init(&msg->objects, 0)) {
    rplidar_ros__msg__ObjectInfoArray__fini(msg);
    return false;
  }
  return true;
}

void
rplidar_ros__msg__ObjectInfoArray__fini(rplidar_ros__msg__ObjectInfoArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // objects
  rplidar_ros__msg__ObjectInfo__Sequence__fini(&msg->objects);
}

rplidar_ros__msg__ObjectInfoArray *
rplidar_ros__msg__ObjectInfoArray__create()
{
  rplidar_ros__msg__ObjectInfoArray * msg = (rplidar_ros__msg__ObjectInfoArray *)malloc(sizeof(rplidar_ros__msg__ObjectInfoArray));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rplidar_ros__msg__ObjectInfoArray));
  bool success = rplidar_ros__msg__ObjectInfoArray__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
rplidar_ros__msg__ObjectInfoArray__destroy(rplidar_ros__msg__ObjectInfoArray * msg)
{
  if (msg) {
    rplidar_ros__msg__ObjectInfoArray__fini(msg);
  }
  free(msg);
}


bool
rplidar_ros__msg__ObjectInfoArray__Sequence__init(rplidar_ros__msg__ObjectInfoArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rplidar_ros__msg__ObjectInfoArray * data = NULL;
  if (size) {
    data = (rplidar_ros__msg__ObjectInfoArray *)calloc(size, sizeof(rplidar_ros__msg__ObjectInfoArray));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rplidar_ros__msg__ObjectInfoArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rplidar_ros__msg__ObjectInfoArray__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rplidar_ros__msg__ObjectInfoArray__Sequence__fini(rplidar_ros__msg__ObjectInfoArray__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rplidar_ros__msg__ObjectInfoArray__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rplidar_ros__msg__ObjectInfoArray__Sequence *
rplidar_ros__msg__ObjectInfoArray__Sequence__create(size_t size)
{
  rplidar_ros__msg__ObjectInfoArray__Sequence * array = (rplidar_ros__msg__ObjectInfoArray__Sequence *)malloc(sizeof(rplidar_ros__msg__ObjectInfoArray__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = rplidar_ros__msg__ObjectInfoArray__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
rplidar_ros__msg__ObjectInfoArray__Sequence__destroy(rplidar_ros__msg__ObjectInfoArray__Sequence * array)
{
  if (array) {
    rplidar_ros__msg__ObjectInfoArray__Sequence__fini(array);
  }
  free(array);
}
