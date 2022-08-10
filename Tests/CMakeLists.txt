FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(ConverterUT ../Backend.cpp ConverterUT.cpp)
set_target_properties(ConverterUT  PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

include(GoogleTest)
gtest_discover_tests(ConverterUT)
