cmake_minimum_required(VERSION 3.29)
project(justify VERSION 0.1.0)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -ansi)
endif()

include(CheckFunctionExists)
check_function_exists(strlcat HAVE_STRLCAT)
if(HAVE_STRLCAT)
    add_definitions(-DHAVE_STRLCAT=1)
endif()

set(SRC_FILES
    src/linebuffer.c
    src/word.c
    src/main.c
)
include_directories(src)
add_executable(justify ${SRC_FILES})

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
