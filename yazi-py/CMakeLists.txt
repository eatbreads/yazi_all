cmake_minimum_required(VERSION 3.19)
project(yazi-py)

set(CMAKE_CXX_STANDARD 11)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(./)

# 包含 python 头文件所在目录
include_directories("C:/Python39/include")

file(GLOB_RECURSE SOURCES "py/*.cpp")

# 链接 python 库文件
link_directories("C:/Python39/libs/")
link_libraries("python3")

add_executable(main ${SOURCES} main.cpp)
