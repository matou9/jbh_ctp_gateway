cmake_minimum_required(VERSION 3.10)
project(client)

#头文件搜索目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#源文件集合
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/1_source/*.cpp)
set(SRC ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/client_main.cpp)

#链接库搜索目录


#链接库


#指定编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -Wall")
#生成可执行文件
add_executable(client ${SRC})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3_build)