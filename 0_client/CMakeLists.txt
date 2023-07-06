cmake_minimum_required(VERSION 3.10)
project(client)

#头文件搜索目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#源文件打包
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/1_source/*.cpp)
set(SRC ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/client_main.cpp)
#指定编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
#生成可执行文件
add_executable(client ${SRC})
#库搜索目录
#链接库
target_link_libraries(client pthread)
#可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/2_build)