#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include "std_msgs/String.h"


//try:
//#include <sensor_msgs/ChannelFloat32>



class ObstacleDetector
{
public:
  ObstacleDetector()
  {
    //Topic you want to publish

    pub_is_obstacle_ = nh_.advertise<std_msgs::String>("is_obstacle",1);
    scan_subscriber_ = nh_.subscribe("/scan", 1, &ObstacleDetector::scanCallback, this);



  }

  void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg){
      std_msgs::String msg;

      ros::NodeHandle n;
      ros::Publisher pub_is_obstacle_;
      pub_is_obstacle_ = n.advertise<std_msgs::String>("is_obstacle",1);

      double size=scan_msg->ranges.size();

      double min_dist= 1;


      ROS_INFO("in callback");

      for (unsigned int x=0;x< scan_msg->ranges.size();x++){

          if(min_dist>scan_msg->ranges[x]){
              min_dist = scan_msg->ranges[x];
          }

      }

      ROS_INFO("min_dist = %f", min_dist);

      if (min_dist<0.2){
          msg.data = "Obstacle detected";
          pub_is_obstacle_.publish(msg);
      }
      else{
          msg.data = "No obstacle";
          pub_is_obstacle_.publish(msg);
      }
  }

private:
  ros::NodeHandle nh_;
  ros::Subscriber scan_subscriber_;
  ros::Publisher pub_is_obstacle_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "obstacle_detector");

  //Create an object of class SubscribeAndPublish that will take care of everything
  ObstacleDetector ODObject;

  ros::spin();

  return 0;
}
