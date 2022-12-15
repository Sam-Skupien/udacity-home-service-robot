#!/bin/sh
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/world/myworld.world;" &
sleep 15

xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/maps/map.yaml initial_pose_x:=-4 initial_pose_y:=-23 initial_pose_a:=0" &
sleep 5

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &


