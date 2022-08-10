#Should work on Windows(MSVC) and Linux.
#To make it work on Mac you have to add another "add_executable" tailored for Mac.

cmake_minimum_required(VERSION 3.21)

project(BinaryConverter)

set(USE_wxWIDGETS ON)

#Main target config
add_executable(${PROJECT_NAME} WIN32 Backend.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

if (USE_wxWIDGETS)
    add_subdirectory(Frontends/wxWidgets)
endif ()

add_subdirectory(Tests)
