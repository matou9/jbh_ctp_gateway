cmake_minimum_required(VERSION 3.10)
project(server)
#定义变量以供子目录使用
set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3_lib) # 库生成目录
set(bin_path ${CMAKE_CURRENT_SOURCE_DIR}/2_build) # 可执行文件生成目录
set(head_path ${CMAKE_CURRENT_SOURCE_DIR}/0_include ${CMAKE_CURRENT_SOURCE_DIR}/1_source) # 头文件目录

#添加子目录
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/1_source/1_future_server/1_CTP_gateway)
#头文件搜索目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${head_path})
#源文件打包
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/1_source/0_server_connector/0_server_connector_implement/*.cpp)
set(SRC ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/server_main.cpp)
#指定编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
#生成可执行文件
add_executable(server ${SRC})
#库搜索目录
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/3_lib)
#链接库
target_link_libraries(server pthread CTP_gateway)
#可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${bin_path})