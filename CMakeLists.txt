cmake_minimum_required(VERSION 3.9)
project(cstring_jslike C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})
find_package(codecov)

add_library(cstring_jslike SHARED cstring_jslike.h cstring_jslike.c)

add_executable(cstring_jslike_test test.c)
target_link_libraries(cstring_jslike_test cstring_jslike)
add_coverage(cstring_jslike_test)

# Run test
enable_testing()
add_test(NAME cstring_jslike_test
        COMMAND "./cstring_jslike_test")

# Unit test
option(BUILD_TEST "Build the unit tests" ON)
if(BUILD_TEST)
    add_subdirectory(externals)
    add_subdirectory(test)
endif()

# evaluate coverage
coverage_evaluate()