cmake_minimum_required(VERSION 3.5)
project(motor_control)

set(CMAKE_CXX_STANDARD 17)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 메시지 생성
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ServoCtrlMsg.msg"
)

include_directories(include)

add_executable(motor_control_node
  src/motor_control_node.cpp
  src/pwm.cpp
)

ament_target_dependencies(motor_control_node
  rclcpp
  std_msgs
)

rosidl_target_interfaces(motor_control_node
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

install(TARGETS motor_control_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
