#include <ros_service/ros_service.hpp>


int main(int argc, char ** argv)
{
    ros::init(argc, argv, "basic_service");

    basic_service::ros_service node;

    node.run();

    return 0;
}