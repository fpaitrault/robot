project(Robot_Target)

INCLUDE_DIRECTORIES(${Robot_Interfaces_BINARY_DIR} ${Robot_Utils_SOURCE_DIR} ${Robot_Target_SOURCE_DIR})
ADD_LIBRARY(robot_target SHARED motorI.cc
                                serial/motorSerial.cc
                                control/motorControl.cc
                                control/realtime/Controller.c
                                control/realtime/Controller_data.c)

ADD_LIBRARY(motor_service SHARED services/motorServiceI.cc)
TARGET_LINK_LIBRARIES(motor_service robot_utils robot_interfaces)
                                