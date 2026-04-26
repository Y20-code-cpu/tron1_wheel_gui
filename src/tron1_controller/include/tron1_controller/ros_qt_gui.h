#ifndef ROS_QT_GUI_H
#define ROS_QT_GUI_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Imu.h>
#include <thread>
#include <mutex>

class RosQtGUI : public QMainWindow {
    Q_OBJECT
    
public:
    RosQtGUI(QWidget *parent = nullptr);
    ~RosQtGUI();
    
private slots:
    // 控制按钮
    void onStandPressed();
    void onWalkPressed();
    void onSitPressed();
    void onStopPressed();
    void onRecoverPressed();
    
    // 速度控制
    void onLinearSpeedChanged(int value);
    void onAngularSpeedChanged(int value);
    
    // 方向控制
    void onForwardPressed();
    void onBackwardPressed();
    void onLeftPressed();
    void onRightPressed();
    
    // 灯光效果
    void onLightEffectChanged(int effect);
    
private:
    void createUI();
    void setupConnections();
    void publishTwist(double linear_x, double angular_z);
    void sendCommand(const std::string& title, const std::string& data = "");
    
    // 回调函数
    void stateCallback(const std_msgs::String::ConstPtr& msg);
    void imuCallback(const sensor_msgs::Imu::ConstPtr& msg);
    
    // ROS 相关
    ros::NodeHandle nh_;
    ros::Publisher cmd_vel_pub_;
    ros::Publisher cmd_json_pub_;
    ros::Subscriber state_sub_;
    ros::Subscriber imu_sub_;
    
    // UI 组件
    QSlider *m_linear_speed_slider;
    QSlider *m_angular_speed_slider;
    QLabel *m_status_label;
    QLabel *m_battery_label;
    QLabel *m_imu_label;
    QLabel *m_connection_label;
    
    QPushButton *m_stand_btn;
    QPushButton *m_walk_btn;
    QPushButton *m_sit_btn;
    QPushButton *m_stop_btn;
    QPushButton *m_recover_btn;
    
    QPushButton *m_forward_btn;
    QPushButton *m_backward_btn;
    QPushButton *m_left_btn;
    QPushButton *m_right_btn;
    
    QComboBox *m_light_effect_combo;
    
    // 状态变量
    double m_current_linear_speed = 0.0;
    double m_current_angular_speed = 0.0;
    std::mutex m_state_mutex;
};

#endif // ROS_QT_GUI_H