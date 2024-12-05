cmake_minimum_required(VERSION 3.19)
project(yazi-async)

set(CMAKE_CXX_STANDARD 14)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(./)

file(GLOB_RECURSE SOURCES "async/*.cpp" "frame/*.cpp" "routine/*.cpp" "socket/*.cpp" "utility/*.cpp")

add_executable(server ${SOURCES} server.cpp)
add_executable(client ${SOURCES} client.cpp)
