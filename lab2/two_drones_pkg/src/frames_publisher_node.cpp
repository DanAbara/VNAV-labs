#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include <iostream>

class FramesPublisherNode {
 private:
  ros::NodeHandle nh;
  ros::Time startup_time;

  ros::Timer heartbeat;

  // Instantiate a transform broadcaster
  tf2_ros::TransformBroadcaster br;

 public:
  FramesPublisherNode() {
    // This method is run once, when the node is launched.
    startup_time = ros::Time::now();
    heartbeat =
        nh.createTimer(ros::Duration(0.02), &FramesPublisherNode::onPublish, this);
    heartbeat.start();
  }

  void onPublish(const ros::TimerEvent&) {
    // This method is called at 50Hz, due to the timer created on line 19.
    // 1. Compute time elapsed in seconds since the node has been started

    ros::Duration elapsed_time = ros::Time::now() - startup_time;
    double time = elapsed_time.toSec();
    
    // Declare two geometry_msgs::TransformStamped objects, which need to be populated
    geometry_msgs::TransformStamped AV1World;
    geometry_msgs::TransformStamped AV2World;
    
    // Set an identity transform by setting just the w component of the rotation, others default to 0
    AV1World.transform.rotation.w = 1.0;
    AV2World.transform.rotation.w = 1.0;

    // 2. Populate the two transforms for the AVs, using the variable "time"
    // AV1's motion is such that roll = 0, pitch = 0, yaw = t
    AV1World.header.stamp = ros::Time::now();
    AV1World.header.frame_id = "world";
    AV1World.child_frame_id = "av1";
    AV1World.transform.translation.x = cos(time);
    AV1World.transform.translation.y = sin(time);
    AV1World.transform.translation.z = 0.0;
    tf2::Quaternion q_av1;
    q_av1.setRPY(0.0, 0.0, time);
    AV1World.transform.rotation.x = q_av1.x();
    AV1World.transform.rotation.y = q_av1.y();
    AV1World.transform.rotation.z = q_av1.z();
    AV1World.transform.rotation.w = q_av1.w();

    // AV2's motion is pure translation
    AV2World.header.stamp = ros::Time::now();
    AV2World.header.frame_id = "world";
    AV2World.child_frame_id = "av2";
    AV2World.transform.translation.x = sin(time);
    AV2World.transform.translation.y = 0.0;
    AV2World.transform.translation.z = cos(2*time);
    
    // 3. Broadcast the transforms using a tf2_ros::TransformBroadcaster (defined as a member of the node class)
    br.sendTransform(AV1World);
    br.sendTransform(AV2World);;
  }
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "frames_publisher_node");
  FramesPublisherNode node;
  ros::spin();
  return 0;
}
