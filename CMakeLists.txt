#Should work on Windows(MSVC) and Linux.
#To make it work on Mac you have to add another "add_executable" tailored for Mac.

cmake_minimum_required(VERSION 3.21)

project(BinaryConverter)

#Source files list (cpp only)
set(SRC_FILES App.cpp Frame.cpp Converter.cpp)

#Set which libs should link to main target
set(LIBS wxbase wxcore)

#Dependencies to delay linking
set(DEPS wxbase wxcore wxhtml wxnet wxxml wxxrc)

#wxWidgets config
#On Linux watch CMake output for possible lack of not required dependencies
set(wxBUILD_SHARED OFF CACHE BOOL "Build wx libraries as shared libs")
set(wxBUILD_PRECOMP OFF CACHE BOOL "Use precompiled headers")
set(wxBUILD_MONOLITHIC OFF CACHE BOOL "Build a single library")
set(wxUSE_STL ON)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
        GIT_TAG v3.1.5
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(wxWidgets)

#Main target config
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
add_dependencies(${PROJECT_NAME} ${DEPS}) #Just to delay linking
if (wxBUILD_SHARED)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WXUSINGDLL=1)
endif ()
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

add_subdirectory(Tests)
