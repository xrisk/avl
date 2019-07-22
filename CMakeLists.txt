cmake_minimum_required(VERSION 3.0)

project(libavl_project)

set(CMAKE_BUILD_TYPE Release)

add_library(avl STATIC avl.c)
add_executable (main main.c)

target_link_libraries(main avl)

install(TARGETS main DESTINATION bin)
