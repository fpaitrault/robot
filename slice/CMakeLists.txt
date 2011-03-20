PROJECT(Robot_Interfaces)

include(slice2cpp.cmake)

SLICE2CPP(hardware.ice ${CMAKE_CURRENT_BINARY_DIR})
SLICE2PY(hardware.ice ${CMAKE_CURRENT_BINARY_DIR})

INCLUDE_DIRECTORIES(${Robot_Interfaces_BINARY_DIR})
ADD_LIBRARY(robot_interfaces SHARED ${Robot_Interfaces_BINARY_DIR}/hardware.cc)