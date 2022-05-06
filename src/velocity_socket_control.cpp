#include "communication.hpp"
#include "control_data.hpp"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include <iostream>

const std::uint16_t PORT = 42421;
const double CYCLE_TIME = 10.0;

auto main(int argc, char **argv) -> int {
  auto control_data = std::make_shared<ControlData>();

  std::cout << "Initializing ROS ... " << std::endl;
  ros::init(argc, argv, "velocity_socket_control");

  Communication::Server server(control_data, PORT);

  ros::NodeHandle node_handle;
  const auto queue_size = 100;
  ros::Publisher publisher =
      node_handle.advertise<geometry_msgs::Twist>("/cmd_vel", queue_size);
  ros::Rate loop_rate(1 / CYCLE_TIME);

  while (ros::ok()) {
    std::cout << "Waiting for new data ... " << std::endl;
    auto commands = control_data->get_new_data();
    for (auto command : commands) {
      if (control_data->has_new_data()) {
        break;
      }
      geometry_msgs::Twist twist;
      twist.linear.x = command.x;
      twist.angular.z = command.phi;
      publisher.publish(twist);
      ros::spinOnce();
      loop_rate.sleep();
    }
  }
  std::cout << "Exiting..." << std::endl;
  return 0;
}
