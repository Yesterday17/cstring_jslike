add_library(unity STATIC
        unity/src/unity.c)

target_include_directories(unity PUBLIC
        unity/src)