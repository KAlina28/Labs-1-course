cmake_minimum_required(VERSION 3.16)
project(lab-02_..strings C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-02_cstrings
        src/str.c
        src/test.c
        src/test_str.c
        include/test_str.h
        include/str.h
        )

target_include_directories(lab-02_cstrings PUBLIC ./include)

