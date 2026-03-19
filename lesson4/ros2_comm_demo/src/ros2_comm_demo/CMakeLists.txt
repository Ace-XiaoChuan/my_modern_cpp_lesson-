cmake_minimum_required(VERSION 3.8)
project(ros2_comm_demo)

# 1. 开启 C++ 17 支持（ROS 2 推荐）
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 2. 查找依赖
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(robot_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

# 3. 添加可执行文件 (Nodes)
# 依次为 src 下的四个文件创建节点
set(NODES
  "battery_node"
  "command_node"
  "pose_node"
  "task_manager_node"
)

foreach(NODE ${NODES})
  add_executable(${NODE} src/${NODE}.cpp)
  # 在这里也要把新依赖加进去
  ament_target_dependencies(${NODE} 
    rclcpp 
    robot_interfaces 
    geometry_msgs 
    std_msgs
  )
endforeach()

# 4. 安装可执行文件到 lib 目录
install(TARGETS
  ${NODES}
  DESTINATION lib/${PROJECT_NAME}
)

# 5. 安装 launch 文件夹 
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# 6. 代码质量检查 (可选)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
