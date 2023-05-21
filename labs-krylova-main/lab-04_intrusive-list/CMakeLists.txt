cmake_minimum_required(VERSION 3.16)
project(lab-04_intrusive-list C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-04_intrusive-list
        src/main.c
        src/clist.c
        include/clist.h
        )

target_include_directories(lab-04_intrusive-list PUBLIC ./include)


