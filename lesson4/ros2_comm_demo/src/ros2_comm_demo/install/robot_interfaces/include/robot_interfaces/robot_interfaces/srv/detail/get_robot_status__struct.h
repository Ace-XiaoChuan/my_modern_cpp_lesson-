// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_interfaces:srv/GetRobotStatus.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__STRUCT_H_
#define ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetRobotStatus in the package robot_interfaces.
typedef struct robot_interfaces__srv__GetRobotStatus_Request
{
  uint8_t structure_needs_at_least_one_member;
} robot_interfaces__srv__GetRobotStatus_Request;

// Struct for a sequence of robot_interfaces__srv__GetRobotStatus_Request.
typedef struct robot_interfaces__srv__GetRobotStatus_Request__Sequence
{
  robot_interfaces__srv__GetRobotStatus_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_interfaces__srv__GetRobotStatus_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'battery_level'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetRobotStatus in the package robot_interfaces.
typedef struct robot_interfaces__srv__GetRobotStatus_Response
{
  rosidl_runtime_c__String battery_level;
  double x;
  double y;
  double z;
  bool has_task;
} robot_interfaces__srv__GetRobotStatus_Response;

// Struct for a sequence of robot_interfaces__srv__GetRobotStatus_Response.
typedef struct robot_interfaces__srv__GetRobotStatus_Response__Sequence
{
  robot_interfaces__srv__GetRobotStatus_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_interfaces__srv__GetRobotStatus_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__STRUCT_H_
