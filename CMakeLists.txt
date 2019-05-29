cmake_minimum_required(VERSION 3.14)
project(skip_list C)

set(CMAKE_C_STANDARD 99)

add_executable(skip_list main.c skiplist.c skiplist.h)