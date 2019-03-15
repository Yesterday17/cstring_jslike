cmake_minimum_required(VERSION 3.13)
project(cstring_jslike C)

set(CMAKE_C_STANDARD 11)

add_executable(cstring_jslike test.c cstring_jslike.h cstring_jslike.c)