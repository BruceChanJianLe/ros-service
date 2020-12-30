#include <ros_service/ros_service.hpp>


int main(int argc, char ** argv)
{
    // Initialize ROS node
    ros::init(argc, argv, "basic_service");

    // Instantiate ros_service obj
    basic_service::ros_service node;

    // Run
    node.run();

    return 0;
}