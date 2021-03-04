#ifndef ROS_SERVICE_H__
#define ROS_SERVICE_H__

#include <ros/ros.h>
#include <ros_service/Service.h>

namespace basic_service
{
    class ros_service
    {
    private:
        ros::NodeHandle private_nh_;
        ros::NodeHandle global_nh_;
        ros::ServiceServer srv_;

    public:
        ros_service();
        ~ros_service();

        void run();
    };
} // namespace basic_service


#endif