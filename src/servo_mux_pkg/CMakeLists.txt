cmake_minimum_required(VERSION 3.5)
project(servo_mux_pkg)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(motor_control REQUIRED)
find_package(rplidar_ros REQUIRED)

add_executable(servo_mux_node
  src/servo_mux_node.cpp)

include_directories(include)

ament_target_dependencies(servo_mux_node
  rclcpp
  std_msgs
  motor_control
  rplidar_ros)

install(TARGETS servo_mux_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include/)


ament_package()
