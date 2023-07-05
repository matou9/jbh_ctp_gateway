cmake_minimum_required(VERSION 3.10)
project(server)

#头文件搜索目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/1_source/*.cpp)
set(SRC ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/server_main.cpp)

#链接库搜索目录


#链接库


#指定编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -pthread")
add_executable(server ${SRC})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3_build)