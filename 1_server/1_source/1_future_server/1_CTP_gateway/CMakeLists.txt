cmake_minimum_required(VERSION 3.10)
project(CTP_gateway)

#头文件搜索目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${head_path})

#源文件打包
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/0_CTP_gateway_implement/*.cpp)
#指定编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

#自定义动态库搜索目录
find_library(CTP_trader thosttraderapi_se HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../0_trading_platform_api/CTP6.3.15/linux)
#寻找外部库(usr/)
find_package(Boost REQUIRED COMPONENTS filesystem)

#库文件输出目录
set(LIBRARY_OUTPUT_PATH ${lib_path})

#生成库文件
add_library(CTP_gateway SHARED ${src})

#链接动态库
target_link_libraries(CTP_gateway pthread Boost::filesystem ${CTP_trader})



