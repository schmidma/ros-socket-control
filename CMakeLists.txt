cmake_minimum_required(VERSION 3.0.2)
project(ros_socket_control)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
)

find_package(nlohmann_json CONFIG REQUIRED)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(velocity_socket_control_node
  src/velocity_socket_control.cpp
  src/communication.cpp
  src/control_data.cpp
  )

target_link_libraries(velocity_socket_control_node
  ${catkin_LIBRARIES}
  nlohmann_json::nlohmann_json
)

install(TARGETS 
  velocity_socket_control_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
