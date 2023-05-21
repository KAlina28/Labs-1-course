cmake_minimum_required(VERSION 3.16)
project(lab-05_c-io C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-05_c-io
        src/main.c
        src/clist.c
        src/point_list.c
        include/clist.h
        include/point_list.h
        )

target_include_directories(lab-05_c-io PUBLIC ./include)

