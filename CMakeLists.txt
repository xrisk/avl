cmake_minimum_required(VERSION 3.9)

set(CMAKE_BUILD_TYPE Release)

project(libavl_project)

set(CMAKE_BUILD_TYPE Release)

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

add_library(avl STATIC avl.c)

target_compile_options(
    avl PRIVATE
        "-O3"
)

add_executable (main main.c)

target_compile_options(
    main PRIVATE
        "-O3"
)

target_link_libraries(main avl)

install(TARGETS main DESTINATION bin)
