#include <ros_service/ros_service_client.hpp>


int main(int argc, char ** argv)
{
    // Initialize ROS node
    ros::init(argc, argv, "basic_service/basic_client");

    // Instantiate ros_service_client obj
    basic_service::ros_service_client node;

    // Run
    node.run();

    // Shutdown ROS node
    ros::shutdown();

    return 0;
}