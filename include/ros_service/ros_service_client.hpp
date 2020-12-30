#ifndef ROS_SERVICE_CLIENT_H_
#define ROS_SERVICE_CLIENT_H_

#include <ros/ros.h>
#include <ros_service/Service.h>

namespace basic_service
{
    class ros_service_client
    {
    private:
        ros::NodeHandle private_nh_;
        ros::NodeHandle global_nh_;
        ros::ServiceClient srv_client_;

        ros_service::Service srv_msg_;

    public:
        ros_service_client();
        ~ros_service_client();

        void run();
    };

} // namespace basic_service


#endif