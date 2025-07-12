set(TEST_LINEBUFFER_SOURCES test_linebuffer.c ../src/linebuffer.c)
set(TEST_WORD_SOURCES test_word.c ../src/word.c)

add_executable(test_linebuffer ${TEST_LINEBUFFER_SOURCES})
add_executable(test_word ${TEST_WORD_SOURCES})

add_test(NAME test_linebuffer COMMAND test_linebuffer)
add_test(NAME test_word COMMAND test_word)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CMOCKA REQUIRED cmocka)
include_directories(${CMOCKA_INCLUDE_DIRS})
target_link_libraries(test_linebuffer ${CMOCKA_LIBRARIES})
target_link_libraries(test_word ${CMOCKA_LIBRARIES})
