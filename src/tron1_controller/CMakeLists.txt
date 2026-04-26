cmake_minimum_required(VERSION 3.0.2)
project(tron1_controller)

# ============================================================
# Qt5 自动处理设置（必须在 find_package 之前！）
# ============================================================
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================
# 查找必需的包
# ============================================================
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  sensor_msgs
)

find_package(Qt5 REQUIRED COMPONENTS 
  Core 
  Gui 
  Widgets
)

# ============================================================
# Catkin 包声明
# ============================================================
catkin_package()

# ============================================================
# 包含目录
# ============================================================
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# ============================================================
# 编译 WebSocket 客户端库
# ============================================================
add_library(websocket_client src/websocket_client.cpp)
target_link_libraries(websocket_client ${catkin_LIBRARIES})

# ============================================================
# 编译主控制器节点
# ============================================================
add_executable(tron1_controller_node src/tron1_controller_node.cpp)
target_link_libraries(tron1_controller_node 
  websocket_client
  ${catkin_LIBRARIES}
)

# ============================================================
# 编译 Qt5 GUI 应用（只需要 .cpp 文件，不需要 .h）
# ============================================================
add_executable(tron1_controller_gui
    src/main.cpp
    src/ros_qt_gui.cpp
    include/tron1_controller/ros_qt_gui.h
    src/websocket_client.cpp
)

# ============================================================
# 链接 Qt5 和 ROS 库
# ============================================================
target_link_libraries(tron1_controller_gui
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    ${catkin_LIBRARIES}
)

# ============================================================
# 添加 Qt5 包含目录
# ============================================================
target_include_directories(tron1_controller_gui PRIVATE 
  include
  ${catkin_INCLUDE_DIRS}
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

# ============================================================
# 强制 MOC 处理
# ============================================================
set_target_properties(tron1_controller_gui PROPERTIES AUTOMOC ON)

# ============================================================
# 安装规则
# ============================================================
install(TARGETS tron1_controller_node tron1_controller_gui websocket_client
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)

install(PROGRAMS scripts/keyboard_control.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  OPTIONAL
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
