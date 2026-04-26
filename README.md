# tron1_wheel_gui
qt与ros相结合，使用控制面板控制机器人运动


操作步骤：
1.登陆机器人主控：ssh guest@<机器人主控ip>

2.在机器人端启动运动控制节点（自动拉起ros master）：
  source /opt/ros/noetic/setup.bash
  source /home/guest/transfer_ws/install/setup.bash
  export ROBOT_TYPE=<当前机器人型号>  eg.WF_TRON1A
  export RL_TYPE=isaacgym
  roslaunch robot_hw pointfoot_hw.launch
  
3.在开发机A端启动桥接节点（必须保持运行）：
  source /opt/ros/noetic/setup.bash
  source ~/tron1_wheel_gui/devel/setup.bash --extend
  export ROS_MASTER_URI=http://<机器人主控ip>:11311
  export ROS_IP=<开发机ip>
  unset ROS_HOSTNAME
  rosrun tron1_controller tron1_controller_node _robot_ip:=<机器人主控ip> _robot_accid:=<机器人序列号>  eg.WF_TRON1A_469
  
4.开发机B端启动GUI控制面板
  source /opt/ros/noetic/setup.bash
  source ~/tron1_wheel_gui/devel/setup.bash --extend
  export ROS_MASTER_URI=http://<机器人主控ip>:11311
  export ROS_IP=<开发机ip>
  unset ROS_HOSTNAME
  rosrun tron1_controller tron1_controller_gui
  
