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


## Reference

- Service with class [link1](https://answers.ros.org/question/214597/service-with-class-method/) [link2](https://answers.ros.org/question/308160/problem-declaring-a-service-server-within-a-class/)