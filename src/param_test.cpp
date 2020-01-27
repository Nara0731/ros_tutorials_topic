#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "param_test");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::String>("node_test",1000);
  int test = 1;
  ros::Rate loop_rate(1);

  while(ros::ok()){
    nh.param<int>("test", test, 2);
    ROS_INFO("test=%d", test);
    //ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
