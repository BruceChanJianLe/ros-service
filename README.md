# ROS Service

This repository demonstrates the usage of ROS services.

**WARNING**  
Do notet that you will not be able compile this package until you rename it to `ros_service` as `ros-service` is considered as illegal to create service or message.  

## Steps to Create a ROS Service

**Step 1**  

Create a package with the following dependencies.  

```bash
catkin_create_pkg ros_service roscpp rospy message_generation message_runtime
```

Note that if your service depends on some packages you should include them here.  

**Step 2**  

Create `srv` directory and service file with content.  
```bash
mkdir srv
touch srv/Service.srv
```

```yaml
# Request service message
bool enabled
---
# Response service message
bool done
```

**Step 3**

Update CMakeLists.txt to build and source service message header.  

```cmake
## Generate services in the 'srv' folder
add_service_files(
  FILES
  Service.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
)
```

And then `catkin_make`, you will be able to source your header through vscode by adding the path `${workspaceFolder}/../../devel/include/`.

**Step 4**

Create a service server node.  

HEADER
```cpp
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

        bool serviceCallback(
            ::ros_service::Service::Request &,
            ::ros_service::Service::Response &
        );

    public:
        ros_service();
        ~ros_service();

        void run();
    };
} // namespace basic_service

#endif
```

SOURCE
```cpp
#include <ros_service/ros_service.hpp>


namespace basic_service
{
    ros_service::ros_service()
    :   private_nh_(ros::NodeHandle("~")),
        global_nh_(ros::NodeHandle())
    {
        // Setup service server
        srv_ = private_nh_.advertiseService("basic_service", & ros_service::serviceCallback, this);
    }


    ros_service::~ros_service()
    {
    }


    bool ros_service::serviceCallback(
        ::ros_service::Service::Request & req,
        ::ros_service::Service::Response & res
    )
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
```


## Reference

- Service with class [link1](https://answers.ros.org/question/214597/service-with-class-method/) [link2](https://answers.ros.org/question/308160/problem-declaring-a-service-server-within-a-class/)