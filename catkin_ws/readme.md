Home service robot:
Initial setup:

mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ..
catkin_make
sudo apt-get update
cd ~/catkin_ws/src
git clone https://github.com/ros-perception/slam_gmapping
git clone https://github.com/turtlebot/turtlebot
git clone https://github.com/turtlebot/turtlebot_interactions
git clone https://github.com/turtlebot/turtlebot_simulator
cd ~/catkin_ws/
source devel/setup.bash
rosdep -i install gmapping
rosdep -i install turtlebot_teleop
rosdep -i install turtlebot_rviz_launchers
rosdep -i install turtlebot_gazebo
catkin_make
source devel/setup.bash


test slam script:
test_slam.sh deploys a turtlebot inside the environment.


test_navigation.sh:
test_navigation.sh can be tested by running the script and then sending it a 2d nav goal. 


pick_object node:
The pick_objects node is used to send commands programmatically to the turtlebot to move it around the map. 


add_markers node:
Models virtual objects in Rviz and then:
Publishes the marker at the pickup zone
Pause 5 seconds
Hide the marker
Pause 5 seconds
Publish the marker at the drop off zone

home_service.sh script:
This script has the add_markers node subscribe to the amcl pose topic and then uses the robots position to pickup and dropoff objects in rviz. 
