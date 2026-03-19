// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_interfaces:srv/GetRobotStatus.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__BUILDER_HPP_
#define ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_interfaces/srv/detail/get_robot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::srv::GetRobotStatus_Request>()
{
  return ::robot_interfaces::srv::GetRobotStatus_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetRobotStatus_Response_has_task
{
public:
  explicit Init_GetRobotStatus_Response_has_task(::robot_interfaces::srv::GetRobotStatus_Response & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::srv::GetRobotStatus_Response has_task(::robot_interfaces::srv::GetRobotStatus_Response::_has_task_type arg)
  {
    msg_.has_task = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::srv::GetRobotStatus_Response msg_;
};

class Init_GetRobotStatus_Response_z
{
public:
  explicit Init_GetRobotStatus_Response_z(::robot_interfaces::srv::GetRobotStatus_Response & msg)
  : msg_(msg)
  {}
  Init_GetRobotStatus_Response_has_task z(::robot_interfaces::srv::GetRobotStatus_Response::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_GetRobotStatus_Response_has_task(msg_);
  }

private:
  ::robot_interfaces::srv::GetRobotStatus_Response msg_;
};

class Init_GetRobotStatus_Response_y
{
public:
  explicit Init_GetRobotStatus_Response_y(::robot_interfaces::srv::GetRobotStatus_Response & msg)
  : msg_(msg)
  {}
  Init_GetRobotStatus_Response_z y(::robot_interfaces::srv::GetRobotStatus_Response::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_GetRobotStatus_Response_z(msg_);
  }

private:
  ::robot_interfaces::srv::GetRobotStatus_Response msg_;
};

class Init_GetRobotStatus_Response_x
{
public:
  explicit Init_GetRobotStatus_Response_x(::robot_interfaces::srv::GetRobotStatus_Response & msg)
  : msg_(msg)
  {}
  Init_GetRobotStatus_Response_y x(::robot_interfaces::srv::GetRobotStatus_Response::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_GetRobotStatus_Response_y(msg_);
  }

private:
  ::robot_interfaces::srv::GetRobotStatus_Response msg_;
};

class Init_GetRobotStatus_Response_battery_level
{
public:
  Init_GetRobotStatus_Response_battery_level()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetRobotStatus_Response_x battery_level(::robot_interfaces::srv::GetRobotStatus_Response::_battery_level_type arg)
  {
    msg_.battery_level = std::move(arg);
    return Init_GetRobotStatus_Response_x(msg_);
  }

private:
  ::robot_interfaces::srv::GetRobotStatus_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::srv::GetRobotStatus_Response>()
{
  return robot_interfaces::srv::builder::Init_GetRobotStatus_Response_battery_level();
}

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__BUILDER_HPP_
