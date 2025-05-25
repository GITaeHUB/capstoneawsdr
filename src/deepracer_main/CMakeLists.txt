cmake_minimum_required(VERSION 3.5)
project(deepracer_main)

set(CMAKE_CXX_STANDARD 17)

# Set dependencies for the package
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(motor_control REQUIRED)


# Include directories
include_directories(
  include
)


# Executable 정의
add_executable(deepracer_node src/deepracer_main.cpp)

# 타겟에 링크
ament_target_dependencies(deepracer_node
  rclcpp
  std_msgs
  motor_control
)

# Install 관련 설정
install(TARGETS deepracer_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
