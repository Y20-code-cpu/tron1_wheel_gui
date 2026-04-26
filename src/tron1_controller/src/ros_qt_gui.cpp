#include "tron1_controller/ros_qt_gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QApplication>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

RosQtGUI::RosQtGUI(QWidget *parent)
    : QMainWindow(parent) {
    
    ROS_INFO("Initializing TRON1 GUI...");
    
    // 初始化 ROS 发布者和订阅者
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    cmd_json_pub_ = nh_.advertise<std_msgs::String>("/tron1/command", 10);
    state_sub_ = nh_.subscribe("/tron1/state", 10, &RosQtGUI::stateCallback, this);
    imu_sub_ = nh_.subscribe("/tron1/imu", 10, &RosQtGUI::imuCallback, this);
    
    // 创建 UI
    createUI();
    setupConnections();
    
    setWindowTitle("🤖 TRON1 轮足机器人控制台");
    resize(1000, 700);
    
    ROS_INFO("GUI initialized successfully");
}

RosQtGUI::~RosQtGUI() {
    ROS_INFO("Shutting down GUI");
}

void RosQtGUI::createUI() {
    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    
    QVBoxLayout *main_layout = new QVBoxLayout(central_widget);
    main_layout->setSpacing(10);
    main_layout->setContentsMargins(10, 10, 10, 10);
    
    // ===================== 连接状态 =====================
    QGroupBox *connection_group = new QGroupBox("📡 连接状态", this);
    QHBoxLayout *connection_layout = new QHBoxLayout(connection_group);
    m_connection_label = new QLabel("🔌 未连接", this);
    m_connection_label->setStyleSheet("color: red; font-weight: bold; font-size: 14px;");
    connection_layout->addWidget(m_connection_label);
    connection_layout->addStretch();
    main_layout->addWidget(connection_group);
    
    // ===================== 机器人状态显示 =====================
    QGroupBox *status_group = new QGroupBox("📊 机器人状态", this);
    QVBoxLayout *status_layout = new QVBoxLayout(status_group);
    
    m_status_label = new QLabel("状态: 未知", this);
    m_status_label->setStyleSheet("font-size: 12px;");
    
    m_battery_label = new QLabel("🔋 电量: --", this);
    m_battery_label->setStyleSheet("font-size: 12px;");
    
    m_imu_label = new QLabel("📐 IMU: 无数据", this);
    m_imu_label->setStyleSheet("font-size: 12px;");
    
    status_layout->addWidget(m_status_label);
    status_layout->addWidget(m_battery_label);
    status_layout->addWidget(m_imu_label);
    
    main_layout->addWidget(status_group);
    
    // ===================== 速度控制区 =====================
    QGroupBox *speed_group = new QGroupBox("⚙️ 速度控制", this);
    QVBoxLayout *speed_layout = new QVBoxLayout(speed_group);
    
    // 线速度
    QHBoxLayout *linear_layout = new QHBoxLayout();
    QLabel *linear_label = new QLabel("线速度 (m/s): ", this);
    linear_label->setMinimumWidth(120);
    m_linear_speed_slider = new QSlider(Qt::Horizontal, this);
    m_linear_speed_slider->setRange(-100, 100);
    m_linear_speed_slider->setValue(0);
    m_linear_speed_slider->setTickPosition(QSlider::TicksBelow);
    m_linear_speed_slider->setTickInterval(10);
    QLabel *linear_value = new QLabel("0.00", this);
    linear_value->setMinimumWidth(50);
    linear_layout->addWidget(linear_label);
    linear_layout->addWidget(m_linear_speed_slider);
    linear_layout->addWidget(linear_value);
    speed_layout->addLayout(linear_layout);
    
    // 角速度
    QHBoxLayout *angular_layout = new QHBoxLayout();
    QLabel *angular_label = new QLabel("角速度 (rad/s): ", this);
    angular_label->setMinimumWidth(120);
    m_angular_speed_slider = new QSlider(Qt::Horizontal, this);
    m_angular_speed_slider->setRange(-100, 100);
    m_angular_speed_slider->setValue(0);
    m_angular_speed_slider->setTickPosition(QSlider::TicksBelow);
    m_angular_speed_slider->setTickInterval(10);
    QLabel *angular_value = new QLabel("0.00", this);
    angular_value->setMinimumWidth(50);
    angular_layout->addWidget(angular_label);
    angular_layout->addWidget(m_angular_speed_slider);
    angular_layout->addWidget(angular_value);
    speed_layout->addLayout(angular_layout);
    
    main_layout->addWidget(speed_group);
    
    // ===================== 方向控制区 =====================
    QGroupBox *direction_group = new QGroupBox("🎮 方向控制", this);
    QGridLayout *direction_layout = new QGridLayout(direction_group);
    direction_layout->setSpacing(5);
    
    m_forward_btn = new QPushButton("⬆️ 前进", this);
    m_backward_btn = new QPushButton("⬇️ 后退", this);
    m_left_btn = new QPushButton("⬅️ 左转", this);
    m_right_btn = new QPushButton("➡️ 右转", this);
    
    m_forward_btn->setMinimumHeight(60);
    m_backward_btn->setMinimumHeight(60);
    m_left_btn->setMinimumHeight(60);
    m_right_btn->setMinimumHeight(60);
    
    direction_layout->addWidget(m_forward_btn, 0, 1);
    direction_layout->addWidget(m_left_btn, 1, 0);
    direction_layout->addWidget(m_backward_btn, 1, 1);
    direction_layout->addWidget(m_right_btn, 1, 2);
    
    main_layout->addWidget(direction_group);
    
    // ===================== 模式控制区 =====================
    QGroupBox *mode_group = new QGroupBox("🚀 模式控制", this);
    QVBoxLayout *mode_layout = new QVBoxLayout(mode_group);
    
    m_stand_btn = new QPushButton("🚀 站立", this);
    m_walk_btn = new QPushButton("🚶 行走模式", this);
    m_sit_btn = new QPushButton("💺 蹲下", this);
    m_stop_btn = new QPushButton("🛑 紧急停止", this);
    m_recover_btn = new QPushButton("🔄 摔倒恢复", this);
    
    m_stand_btn->setMinimumHeight(50);
    m_walk_btn->setMinimumHeight(50);
    m_sit_btn->setMinimumHeight(50);
    m_stop_btn->setMinimumHeight(50);
    m_recover_btn->setMinimumHeight(50);
    
    m_stop_btn->setStyleSheet("background-color: #ff6b6b; color: white; font-weight: bold;");
    
    QHBoxLayout *btn_layout1 = new QHBoxLayout();
    btn_layout1->addWidget(m_stand_btn);
    btn_layout1->addWidget(m_walk_btn);
    btn_layout1->addWidget(m_sit_btn);
    mode_layout->addLayout(btn_layout1);
    
    QHBoxLayout *btn_layout2 = new QHBoxLayout();
    btn_layout2->addWidget(m_stop_btn);
    btn_layout2->addWidget(m_recover_btn);
    btn_layout2->addStretch();
    mode_layout->addLayout(btn_layout2);
    
    main_layout->addWidget(mode_group);
    
    // ===================== 灯光控制区 =====================
    QGroupBox *light_group = new QGroupBox("💡 灯光效果", this);
    QHBoxLayout *light_layout = new QHBoxLayout(light_group);
    
    m_light_effect_combo = new QComboBox(this);
    m_light_effect_combo->addItem("🔴 红色", 0);
    m_light_effect_combo->addItem("🟢 绿色", 1);
    m_light_effect_combo->addItem("🔵 蓝色", 2);
    m_light_effect_combo->addItem("🔷 青色", 3);
    m_light_effect_combo->addItem("🟣 紫色", 4);
    m_light_effect_combo->addItem("🟡 黄色", 5);
    m_light_effect_combo->addItem("⚪ 白色", 6);
    
    light_layout->addWidget(new QLabel("效果: ", this));
    light_layout->addWidget(m_light_effect_combo);
    light_layout->addStretch();
    
    main_layout->addWidget(light_group);
    
    main_layout->addStretch();
}

void RosQtGUI::setupConnections() {
    // 模式按钮
    connect(m_stand_btn, &QPushButton::clicked, this, &RosQtGUI::onStandPressed);
    connect(m_walk_btn, &QPushButton::clicked, this, &RosQtGUI::onWalkPressed);
    connect(m_sit_btn, &QPushButton::clicked, this, &RosQtGUI::onSitPressed);
    connect(m_stop_btn, &QPushButton::clicked, this, &RosQtGUI::onStopPressed);
    connect(m_recover_btn, &QPushButton::clicked, this, &RosQtGUI::onRecoverPressed);
    
    // 方向按钮
    connect(m_forward_btn, &QPushButton::clicked, this, &RosQtGUI::onForwardPressed);
    connect(m_backward_btn, &QPushButton::clicked, this, &RosQtGUI::onBackwardPressed);
    connect(m_left_btn, &QPushButton::clicked, this, &RosQtGUI::onLeftPressed);
    connect(m_right_btn, &QPushButton::clicked, this, &RosQtGUI::onRightPressed);
    
    // 速度滑块
    connect(m_linear_speed_slider, QOverload<int>::of(&QSlider::valueChanged),
            this, &RosQtGUI::onLinearSpeedChanged);
    connect(m_angular_speed_slider, QOverload<int>::of(&QSlider::valueChanged),
            this, &RosQtGUI::onAngularSpeedChanged);
    
    // 灯光
    connect(m_light_effect_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &RosQtGUI::onLightEffectChanged);
}

void RosQtGUI::onStandPressed() {
    ROS_INFO("🚀 Stand command sent");
    m_status_label->setText("状态: 执行站立...");
    sendCommand("request_stand_mode");
}

void RosQtGUI::onWalkPressed() {
    ROS_INFO("🚶 Walk mode command sent");
    m_status_label->setText("状态: 切换行走模式...");
    sendCommand("request_walk_mode");
}

void RosQtGUI::onSitPressed() {
    ROS_INFO("💺 Sit command sent");
    m_status_label->setText("状态: 执行蹲下...");
    sendCommand("request_sitdown");
}

void RosQtGUI::onStopPressed() {
    ROS_INFO("🛑 Emergency stop!");
    m_linear_speed_slider->blockSignals(true);
    m_angular_speed_slider->blockSignals(true);
    
    m_linear_speed_slider->setValue(0);
    m_angular_speed_slider->setValue(0);
    
    m_linear_speed_slider->blockSignals(false);
    m_angular_speed_slider->blockSignals(false);
    
    m_current_linear_speed = 0.0;
    m_current_angular_speed = 0.0;
    
    publishTwist(0.0, 0.0);
    sendCommand("request_emgy_stop");
    m_status_label->setText("状态: 🛑 已停止");
}

void RosQtGUI::onRecoverPressed() {
    ROS_INFO("🔄 Recover command sent");
    m_status_label->setText("状态: 恢复中...");
    sendCommand("request_recover");
}

void RosQtGUI::onLinearSpeedChanged(int value) {
    m_current_linear_speed = value * 3.0 / 100.0;  // -3.0 ~ 3.0 m/s
    publishTwist(m_current_linear_speed, m_current_angular_speed);
}

void RosQtGUI::onAngularSpeedChanged(int value) {
    m_current_angular_speed = value * 1.5 / 100.0;  // -1.5 ~ 1.5 rad/s
    publishTwist(m_current_linear_speed, m_current_angular_speed);
}

void RosQtGUI::onForwardPressed() {
    ROS_INFO("⬆️ Forward!");
    m_linear_speed_slider->blockSignals(true);
    m_linear_speed_slider->setValue(70);  // 70% = 2.1 m/s
    m_linear_speed_slider->blockSignals(false);
}

void RosQtGUI::onBackwardPressed() {
    ROS_INFO("⬇️ Backward!");
    m_linear_speed_slider->blockSignals(true);
    m_linear_speed_slider->setValue(-70);  // -70% = -2.1 m/s
    m_linear_speed_slider->blockSignals(false);
}

void RosQtGUI::onLeftPressed() {
    ROS_INFO("⬅️ Turn left!");
    m_angular_speed_slider->blockSignals(true);
    m_angular_speed_slider->setValue(80);  // 80% = 1.2 rad/s
    m_angular_speed_slider->blockSignals(false);
}

void RosQtGUI::onRightPressed() {
    ROS_INFO("➡️ Turn right!");
    m_angular_speed_slider->blockSignals(true);
    m_angular_speed_slider->setValue(-80);  // -80% = -1.2 rad/s
    m_angular_speed_slider->blockSignals(false);
}

void RosQtGUI::onLightEffectChanged(int effect) {
    ROS_INFO("💡 Light effect changed to: %d", effect);
    // 这里可以发送灯光命令到机器人
}

void RosQtGUI::publishTwist(double linear_x, double angular_z) {
    geometry_msgs::Twist twist;
    twist.linear.x = linear_x;
    twist.linear.y = 0.0;
    twist.linear.z = 0.0;
    twist.angular.x = 0.0;
    twist.angular.y = 0.0;
    twist.angular.z = angular_z;
    
    cmd_vel_pub_.publish(twist);
}

void RosQtGUI::sendCommand(const std::string& title, const std::string& data) {
    json cmd = {
        {"title", title},
        {"data", json::object()}
    };

    if (!data.empty()) {
        cmd["data"] = data;
    }

    std_msgs::String msg;
    msg.data = cmd.dump();
    cmd_json_pub_.publish(msg);
    ROS_INFO("Command: %s", title.c_str());
}

void RosQtGUI::stateCallback(const std_msgs::String::ConstPtr& msg) {
    try {
        json state_json = json::parse(msg->data);
        
        if (state_json.contains("data")) {
            auto& data = state_json["data"];
            
            if (data.contains("status")) {
                std::string status = data["status"];
                m_status_label->setText(QString::fromStdString("状态: " + status));
                m_connection_label->setText("✅ 已连接");
                m_connection_label->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");
            }
            
            if (data.contains("battery")) {
                int battery_value = 0;
                if (data["battery"].is_number_integer()) {
                    battery_value = data["battery"].get<int>();
                } else if (data["battery"].is_string()) {
                    battery_value = std::stoi(data["battery"].get<std::string>());
                }
                QString battery_text = QString::asprintf("🔋 电量: %d%%", battery_value);
                m_battery_label->setText(battery_text);
            }
        }
    } catch (const std::exception& e) {
        ROS_WARN("Failed to parse state message: %s", e.what());
    }
}

void RosQtGUI::imuCallback(const sensor_msgs::Imu::ConstPtr& msg) {
    QString imu_text = QString::asprintf(
        "📐 IMU - 加速度: [%.2f, %.2f, %.2f] m/s²",
        msg->linear_acceleration.x,
        msg->linear_acceleration.y,
        msg->linear_acceleration.z);
    m_imu_label->setText(imu_text);
}
