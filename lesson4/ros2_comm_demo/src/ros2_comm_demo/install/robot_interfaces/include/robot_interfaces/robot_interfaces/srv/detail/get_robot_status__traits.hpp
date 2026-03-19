// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_interfaces:srv/GetRobotStatus.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__TRAITS_HPP_
#define ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_interfaces/srv/detail/get_robot_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetRobotStatus_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetRobotStatus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetRobotStatus_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace robot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_interfaces::srv::GetRobotStatus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_interfaces::srv::GetRobotStatus_Request & msg)
{
  return robot_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_interfaces::srv::GetRobotStatus_Request>()
{
  return "robot_interfaces::srv::GetRobotStatus_Request";
}

template<>
inline const char * name<robot_interfaces::srv::GetRobotStatus_Request>()
{
  return "robot_interfaces/srv/GetRobotStatus_Request";
}

template<>
struct has_fixed_size<robot_interfaces::srv::GetRobotStatus_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robot_interfaces::srv::GetRobotStatus_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robot_interfaces::srv::GetRobotStatus_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace robot_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetRobotStatus_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: battery_level
  {
    out << "battery_level: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_level, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << ", ";
  }

  // member: has_task
  {
    out << "has_task: ";
    rosidl_generator_traits::value_to_yaml(msg.has_task, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetRobotStatus_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: battery_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_level: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_level, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: has_task
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "has_task: ";
    rosidl_generator_traits::value_to_yaml(msg.has_task, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetRobotStatus_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace robot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_interfaces::srv::GetRobotStatus_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_interfaces::srv::GetRobotStatus_Response & msg)
{
  return robot_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_interfaces::srv::GetRobotStatus_Response>()
{
  return "robot_interfaces::srv::GetRobotStatus_Response";
}

template<>
inline const char * name<robot_interfaces::srv::GetRobotStatus_Response>()
{
  return "robot_interfaces/srv/GetRobotStatus_Response";
}

template<>
struct has_fixed_size<robot_interfaces::srv::GetRobotStatus_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_interfaces::srv::GetRobotStatus_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_interfaces::srv::GetRobotStatus_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robot_interfaces::srv::GetRobotStatus>()
{
  return "robot_interfaces::srv::GetRobotStatus";
}

template<>
inline const char * name<robot_interfaces::srv::GetRobotStatus>()
{
  return "robot_interfaces/srv/GetRobotStatus";
}

template<>
struct has_fixed_size<robot_interfaces::srv::GetRobotStatus>
  : std::integral_constant<
    bool,
    has_fixed_size<robot_interfaces::srv::GetRobotStatus_Request>::value &&
    has_fixed_size<robot_interfaces::srv::GetRobotStatus_Response>::value
  >
{
};

template<>
struct has_bounded_size<robot_interfaces::srv::GetRobotStatus>
  : std::integral_constant<
    bool,
    has_bounded_size<robot_interfaces::srv::GetRobotStatus_Request>::value &&
    has_bounded_size<robot_interfaces::srv::GetRobotStatus_Response>::value
  >
{
};

template<>
struct is_service<robot_interfaces::srv::GetRobotStatus>
  : std::true_type
{
};

template<>
struct is_service_request<robot_interfaces::srv::GetRobotStatus_Request>
  : std::true_type
{
};

template<>
struct is_service_response<robot_interfaces::srv::GetRobotStatus_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATUS__TRAITS_HPP_
