// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rplidar_ros:msg/ObjectInfo.idl
// generated code does not contain a copyright notice
#include "rplidar_ros/msg/detail/object_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
rplidar_ros__msg__ObjectInfo__init(rplidar_ros__msg__ObjectInfo * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  // distance
  return true;
}

void
rplidar_ros__msg__ObjectInfo__fini(rplidar_ros__msg__ObjectInfo * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
  // distance
}

rplidar_ros__msg__ObjectInfo *
rplidar_ros__msg__ObjectInfo__create()
{
  rplidar_ros__msg__ObjectInfo * msg = (rplidar_ros__msg__ObjectInfo *)malloc(sizeof(rplidar_ros__msg__ObjectInfo));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rplidar_ros__msg__ObjectInfo));
  bool success = rplidar_ros__msg__ObjectInfo__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
rplidar_ros__msg__ObjectInfo__destroy(rplidar_ros__msg__ObjectInfo * msg)
{
  if (msg) {
    rplidar_ros__msg__ObjectInfo__fini(msg);
  }
  free(msg);
}


bool
rplidar_ros__msg__ObjectInfo__Sequence__init(rplidar_ros__msg__ObjectInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rplidar_ros__msg__ObjectInfo * data = NULL;
  if (size) {
    data = (rplidar_ros__msg__ObjectInfo *)calloc(size, sizeof(rplidar_ros__msg__ObjectInfo));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rplidar_ros__msg__ObjectInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rplidar_ros__msg__ObjectInfo__fini(&data[i - 1]);
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
rplidar_ros__msg__ObjectInfo__Sequence__fini(rplidar_ros__msg__ObjectInfo__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rplidar_ros__msg__ObjectInfo__fini(&array->data[i]);
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

rplidar_ros__msg__ObjectInfo__Sequence *
rplidar_ros__msg__ObjectInfo__Sequence__create(size_t size)
{
  rplidar_ros__msg__ObjectInfo__Sequence * array = (rplidar_ros__msg__ObjectInfo__Sequence *)malloc(sizeof(rplidar_ros__msg__ObjectInfo__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = rplidar_ros__msg__ObjectInfo__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
rplidar_ros__msg__ObjectInfo__Sequence__destroy(rplidar_ros__msg__ObjectInfo__Sequence * array)
{
  if (array) {
    rplidar_ros__msg__ObjectInfo__Sequence__fini(array);
  }
  free(array);
}
