cmake_minimum_required(VERSION 3.16)
project(lab-11_vector CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-11_vector
        src/main.cpp
        include/my_vector.hpp
        include/my_vector_impl.hpp
        )

target_include_directories(lab-11_vector PUBLIC ./include)