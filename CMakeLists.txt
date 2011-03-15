project(Robot)
cmake_minimum_required(VERSION 2.8)
include(slice2cpp.cmake)

SLICE2CPP(slice/motor.ice ${CMAKE_CURRENT_BINARY_DIR})
SLICE2PY(slice/motor.ice ${CMAKE_CURRENT_BINARY_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
ADD_LIBRARY(motor_service SHARED services/motorServiceI.cc
                                 impl/IceCom/motorI.cc
                                 impl/serial/motorSerial.cc
                                 impl/control/motorControl.cc
                                 impl/control/realtime/Controller.c
                                 impl/control/realtime/Controller_data.c
                                 impl/shared/RTThread.cc
                                 ${CMAKE_CURRENT_BINARY_DIR}/motor.cc)
                                 
ADD_EXECUTABLE(robot_control client/main.cc ${CMAKE_CURRENT_BINARY_DIR}/motor.cc)
TARGET_LINK_LIBRARIES(robot_control Ice IceUtil)
