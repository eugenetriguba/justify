cmake_minimum_required(VERSION 3.29)
project(justify VERSION 0.1.2)
include_directories(${CMAKE_SOURCE_DIR}/include)

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

include(CheckFunctionExists)
check_function_exists(strlcat HAVE_STRLCAT)
if(HAVE_STRLCAT)
    add_definitions(-DHAVE_STRLCAT=1)
else()
    list(APPEND SRC_FILES src/strlcat.c)
endif()

include_directories(src)
add_executable(justify ${SRC_FILES})

install(TARGETS justify RUNTIME DESTINATION bin)
install(FILES doc/justify.1 DESTINATION share/man/man1)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
