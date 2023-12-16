cmake_minimum_required(VERSION 3.12)
project(my_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
# 项目根目录
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# 源码目录
set(SRC_DIR ${ROOT_DIR}/src)
# 头文件目录
set(INC_DIR ${ROOT_DIR}/include)

# 源文件
set(MAIN_SRC_FILE ${ROOT_DIR/main.cpp})

add_executable(my_server main.cpp)