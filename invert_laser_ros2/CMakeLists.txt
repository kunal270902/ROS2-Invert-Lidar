cmake_minimum_required(VERSION 3.5)
project(invert_laser)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

include_directories(include)

# Create the executable
add_executable(${PROJECT_NAME}_node src/invert_laser_node.cpp)

# Specify the libraries to link against
ament_target_dependencies(${PROJECT_NAME}_node
  rclcpp
  sensor_msgs
)

# Install the executable
install(TARGETS
  ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install other files if necessary
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
