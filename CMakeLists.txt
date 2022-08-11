#Should work on Windows(MSVC) and Linux.
#To make it work on Mac you have to add another "add_executable" tailored for Mac.

cmake_minimum_required(VERSION 3.21)
include(FetchContent)

project(BinaryConverter)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BACKEND_SRC ${CMAKE_SOURCE_DIR}/Backend.cpp)

#Set frontend lib
set(USE_wxWIDGETS OFF CACHE BOOL "Use wxWidgets frontend" FORCE)

if (USE_wxWIDGETS)
    add_subdirectory(Frontends/wxWidgets)
else ()
    add_subdirectory(Frontends/xtd)
endif ()

add_subdirectory(Tests)
