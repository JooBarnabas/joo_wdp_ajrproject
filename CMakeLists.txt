cmake_minimum_required(VERSION 3.5)
project(distance_pkg)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(distance_nodes src/distance_nodes.cpp)
ament_target_dependencies(distance_nodes rclcpp sensor_msgs)

install(TARGETS distance_nodes DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

ament_package()
