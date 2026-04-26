#include <QApplication>
#include <ros/ros.h>
#include <thread>
#include "tron1_controller/ros_qt_gui.h"

// ROS 自旋线程
void rosSpinThread() {
    ros::spin();
}

int main(int argc, char** argv) {
    // 初始化 ROS
    ros::init(argc, argv, "tron1_controller_gui");
    
    // 在后台线程中启动 ROS spin
    std::thread ros_thread(rosSpinThread);
    ros_thread.detach();
    
    // 启动 Qt 应用
    QApplication app(argc, argv);
    
    RosQtGUI window;
    window.show();
    
    int result = app.exec();
    
    // 关闭 ROS
    ros::shutdown();
    
    return result;
}
