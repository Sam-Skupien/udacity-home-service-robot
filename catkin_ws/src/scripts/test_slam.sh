#!/bin/sh
xterm -e "export ROBOT_INITIAL_POSE='-x -0 -y -0 -z 0 -R 0 -P 0 -Y 0';
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/world/myworld.world;" &
sleep 5

