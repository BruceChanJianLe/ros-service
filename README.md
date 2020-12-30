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

**Step 5**  

Update CMakeLists.txt for service server.  

```cmake
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES ros_service
#  CATKIN_DEPENDS message_generation message_runtime roscpp rospy
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(ros_service_node
  src/ros_service.cpp
  src/ros_service_node.cpp
)
add_dependencies(ros_service_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ros_service_node ${catkin_LIBRARIES})
```

**Step 6**  

Creating a service client.  

HEADER
```cpp
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
```

SOURCE
```cpp
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
```

## Reference

- Service with class [link1](https://answers.ros.org/question/214597/service-with-class-method/) [link2](https://answers.ros.org/question/308160/problem-declaring-a-service-server-within-a-class/)