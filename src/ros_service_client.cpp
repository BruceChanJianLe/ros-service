#include <ros_service/ros_service_client.hpp>


namespace basic_service
{
    ros_service_client::ros_service_client()
    :   private_nh_(ros::NodeHandle("~")),
        global_nh_(ros::NodeHandle()),
        srv_client_(global_nh_.serviceClient<ros_service::Service>("ros_service_server_node/basic_service"))
    {
    }


    ros_service_client::~ros_service_client()
    {
    }


    void ros_service_client::run()
    {
        // Set service request content
        srv_msg_.request.enabled = true;

        if(srv_client_.call(srv_msg_))
        {
            ROS_INFO_STREAM(
                ros::this_node::getName() <<
                " successfully enabled service client: " <<
                srv_msg_.response.done
            );
        }
        else
        {
            ROS_INFO_STREAM(
                ros::this_node::getName() <<
                " failed to enable service client: " <<
                srv_client_.getService()
            );
        }

    }
} // namespace basic_service
