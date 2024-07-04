cmake_minimum_required(VERSION 3.29)
project(justify VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -ansi)
endif()

set(SRC_FILES
    src/linebuffer.c
    src/word.c
    src/main.c
)
include_directories(src)
add_executable(justify ${SRC_FILES})
