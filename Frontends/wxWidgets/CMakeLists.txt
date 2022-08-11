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

Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
        GIT_TAG v3.1.5
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(wxWidgets)

add_executable(${PROJECT_NAME} WIN32 App.cpp Frame.cpp ${BACKEND_SRC})
add_dependencies(${PROJECT_NAME} ${DEPS}) #Just to delay linking
if (wxBUILD_SHARED)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WXUSINGDLL=1)
endif ()
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
