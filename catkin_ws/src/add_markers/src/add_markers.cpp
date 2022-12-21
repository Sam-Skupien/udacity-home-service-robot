#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <tf/tf.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <math.h>

float tolerance = 0.15f;
float globalCBx = 0.0f; 
float globalCBy = 0.0f;


void poseCB(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
  ::globalCBx = msg->pose.pose.position.x;
  ::globalCBy = msg->pose.pose.position.y;
ROS_INFO_STREAM("msg pose x: " << msg->pose.pose.position.x);
ROS_INFO_STREAM("msg pose y: " << msg->pose.pose.position.y);
}

bool hasConverged(float currX, float currY, float goalX, float goalY) {
  return (fabs(currX - goalX) < tolerance) && (fabs(currY - goalY) < tolerance);
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odomSub = n.subscribe("/amcl_pose", 1000, poseCB);
 


  // Publish the marker
  while (marker_pub.getNumSubscribers() < 1) {
    if (!ros::ok()) {
       return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 31.0;
    marker.pose.position.y = 26.0;
    marker.pose.position.z = 0.1;
    marker.pose.orientation = tf::createQuaternionMsgFromYaw(1.57);

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    marker_pub.publish(marker);

   while(ros::ok()){
    
    ROS_INFO("Moving towards goal");

    while(!hasConverged(globalCBx, globalCBy, 31.0, 26.0)) {
       ROS_INFO_STREAM("Moving towards object. Current x: " << globalCBx << " Current y: " << globalCBy);
ros::spinOnce();
    }
    ROS_INFO("Picked up object!");

    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);

    ros::Duration(5.0).sleep();

    marker.pose.position.x = 29.0;
    marker.pose.position.y = 19.0;
    marker.pose.position.z = 0.1;
    marker.pose.orientation = tf::createQuaternionMsgFromYaw(1.57);

    while(!hasConverged(globalCBx, globalCBy, 29.0, 19.0)) {
       ROS_INFO_STREAM("Moving towards object dropoff. Current x: " << globalCBx << " Current y: " << globalCBy);
ros::spinOnce();
    }
    ROS_INFO("Dropped off object!");
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ros::Duration(5.0).sleep();
    return 0;
}
 
}
