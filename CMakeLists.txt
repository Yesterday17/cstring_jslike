cmake_minimum_required(VERSION 3.9)
project(cstring_jslike C)

set(CMAKE_C_STANDARD 11)

add_library(cstring_jslike SHARED cstring_jslike.h cstring_jslike.c)

add_executable(cstring_jslike_test test.c)
target_link_libraries(cstring_jslike_test cstring_jslike)

enable_testing()
add_test(NAME cstring_jslike_test
        COMMAND "./cstring_jslike_test")