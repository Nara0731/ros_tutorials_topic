#include "ros/ros.h"
#include "ros_tutorials_topic/SrvTutorial.h"

typedef enum{PLUS=1, MINUS, MULTIPLICATION, DIVISION}mehod_item;
int g_operator = PLUS;

bool calculation(ros_tutorials_topic::SrvTutorial::Request &req,
                 ros_tutorials_topic::SrvTutorial::Response &res)
{
  switch(g_operator)
  {
  case PLUS:
    res.result = req.a + req.b; break;
  case MINUS:
    res.result = req.a - req.b; break;
  case MULTIPLICATION:
    res.result = req.a * req.b; break;
  case DIVISION:
    if (req.b == 0){
      res.result = 0; break;
  }else{
    res.result = req.a / req.b; break;
  }
  default:
    res.result = req.a + req.b; break;
  }

  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("response: z=%ld", (long int)res.result);

  return true;
}

int main(int argc, char *argv[])
{
  int test = 1;
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;
  ros::NodeHandle n;
  n.setParam("test", 1);
  //nh.setParam("calculation_method", PLUS);

  ros::ServiceServer ros_tutorials_service_server = nh.advertiseService("ros_tutorial_srv", calculation);

  ROS_INFO("ready srv server");

  ros::Rate loop_rate(10);

  while(ros::ok())
  {
    //nh.getParam("calculation_method", g_operator);
    nh.param<int>("calculation_method", g_operator, PLUS);
    n.getParam("test", test);
    ROS_INFO("test=%d", test);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
