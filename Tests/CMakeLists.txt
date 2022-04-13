FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(ConverterUT ../Converter.cpp ConverterUT.cpp)
set_target_properties(ConverterUT  PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_link_libraries(ConverterUT PUBLIC gtest_main PRIVATE ${LIBS})
add_dependencies(ConverterUT ${DEPS}) #Just to delay linking

include(GoogleTest)
gtest_discover_tests(ConverterUT)
