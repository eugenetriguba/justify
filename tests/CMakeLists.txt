add_executable(test_linebuffer test_linebuffer.c ../src/linebuffer.c)
add_test(NAME test_linebuffer COMMAND test_linebuffer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CMOCKA REQUIRED cmocka)
include_directories(${CMOCKA_INCLUDE_DIRS})
target_link_libraries(test_linebuffer ${CMOCKA_LIBRARIES})
