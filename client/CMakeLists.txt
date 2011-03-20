PROJECT(Robot_Client)

INCLUDE_DIRECTORIES(${Robot_Interfaces_BINARY_DIR})
ADD_EXECUTABLE(robot_control main.cc)
TARGET_LINK_LIBRARIES(robot_control Ice IceUtil robot_interfaces)
