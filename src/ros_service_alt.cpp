#include <ros_service/ros_service_alt.hpp>


namespace basic_service
{
    ros_service::ros_service()
    :   private_nh_(ros::NodeHandle("~")),
        global_nh_(ros::NodeHandle())
    {
        // Setup service server in lambda method
        srv_ = private_nh_.advertiseService<::ros_service::Service::Request, ::ros_service::Service::Response>(
            "basic_service",
            [this](
                ::ros_service::Service::Request & req,
                ::ros_service::Service::Response & res
            ) -> bool
            {
                bool isok = false;
                if(req.enabled)
                {
                    ROS_INFO_STREAM(ros::this_node::getName() << " service enabled(" << req.enabled << ")");
                    res.done = isok = true;
                }
                else
                {
                    ROS_INFO_STREAM(ros::this_node::getName() << " service disabled(" << req.enabled << ")");
                    res.done = isok = true;
                }

                return isok;
            }
        );
    }


    ros_service::~ros_service()
    {
    }


    void ros_service::run()
    {
        ros::Rate r(1);

        while(private_nh_.ok())
        {
            ros::spinOnce();
            r.sleep();
        }
    }
} // namespace basic_service