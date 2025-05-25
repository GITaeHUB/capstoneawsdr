cmake_minimum_required(VERSION 3.5)
project(camera_pkg)

# C 및 C++ 표준 설정
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# 컴파일 옵션 (경고 표시)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 의존성 패키지
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(motor_control REQUIRED)
find_package(rplidar_ros REQUIRED)

# camera_node 빌드
add_executable(camera_node
  src/camera_node.cpp
)
target_include_directories(camera_node PRIVATE
  ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(camera_node
  ${OpenCV_LIBRARIES}
)
ament_target_dependencies(camera_node
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  OpenCV
)

# lane_detection_node 빌드
add_executable(lane_detection_node
  src/lane_detection_node.cpp
)
target_include_directories(lane_detection_node PRIVATE
  ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(lane_detection_node
  ${OpenCV_LIBRARIES}
)
ament_target_dependencies(lane_detection_node
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  OpenCV
  motor_control
  rplidar_ros
)

# lane_detection_node_queue 빌드 (새 추가)
add_executable(lane_detection_node_queue
  src/lane_detection_node_queue.cpp
)
target_include_directories(lane_detection_node_queue PRIVATE
  ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(lane_detection_node_queue
  ${OpenCV_LIBRARIES}
)
ament_target_dependencies(lane_detection_node_queue
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  OpenCV
  motor_control
  rplidar_ros
)

# 실행 파일 설치
install(TARGETS
  camera_node
  lane_detection_node
  lane_detection_node_queue
  DESTINATION lib/${PROJECT_NAME}
)

# launch 디렉토리 설치
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

# export 설정
ament_export_include_directories(include)
ament_export_dependencies(sensor_msgs std_msgs motor_control rplidar_ros)

# 빌드 테스트 관련
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
