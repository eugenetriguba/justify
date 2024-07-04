#include "linebuffer.h"
// clang-format off
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
// clang-format on
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_linebuffer_create(void **state) {
    const int buffer_capacity = 50;
    LineBuffer *lb = linebuffer_create(buffer_capacity);
    assert_non_null(lb);
    assert_int_equal(lb->_buffer_capacity, buffer_capacity);
    assert_int_equal(lb->_buffer_length, 0);
    assert_int_equal(lb->_num_words, 0);
    linebuffer_destroy(lb);
}

void test_linebuffer_append_word(void **state) {
    LineBuffer *lb = linebuffer_create(50);
    assert_non_null(lb);

    linebuffer_append_word(lb, "hello");
    assert_string_equal(lb->_buffer, "hello");
    assert_int_equal(lb->_buffer_length, 5);
    assert_int_equal(lb->_num_words, 1);

    linebuffer_append_word(lb, "world");
    assert_string_equal(lb->_buffer, "hello world");
    assert_int_equal(lb->_buffer_length, 11);
    assert_int_equal(lb->_num_words, 2);

    linebuffer_destroy(lb);
}

void test_linebuffer_space_remaining(void **state) {
    LineBuffer *lb = linebuffer_create(50);
    assert_non_null(lb);

    linebuffer_append_word(lb, "hello");
    assert_int_equal(linebuffer_space_remaining(lb), 45);

    linebuffer_append_word(lb, "world");
    assert_int_equal(linebuffer_space_remaining(lb), 39);

    linebuffer_append_word(lb, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    printf("%ld\n", linebuffer_space_remaining(lb));
    assert_int_equal(linebuffer_space_remaining(lb), 0);

    linebuffer_destroy(lb);
}

void test_linebuffer_write(void **state) {
    LineBuffer *lb = linebuffer_create(50);
    assert_non_null(lb);

    linebuffer_append_word(lb, "hello");
    linebuffer_append_word(lb, "world");

    FILE *fp = tmpfile();
    assert_non_null(fp);
    linebuffer_write(lb, fp);

    rewind(fp);
    char buffer[50];
    fgets(buffer, sizeof(buffer), fp);
    assert_string_equal(buffer, "hello world");

    fclose(fp);
    linebuffer_destroy(lb);
}

void test_linebuffer_write_justified(void **state) {
    LineBuffer *lb = linebuffer_create(20);
    assert_non_null(lb);

    linebuffer_append_word(lb, "hello");
    linebuffer_append_word(lb, "world");

    FILE *fp = tmpfile();
    assert_non_null(fp);
    linebuffer_write_justified(lb, fp);

    rewind(fp);
    char buffer[50];
    fgets(buffer, sizeof(buffer), fp);
    assert_string_equal(buffer, "hello     world\n");

    fclose(fp);
    linebuffer_destroy(lb);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_linebuffer_create),
        cmocka_unit_test(test_linebuffer_append_word),
        cmocka_unit_test(test_linebuffer_space_remaining),
        cmocka_unit_test(test_linebuffer_write),
        // cmocka_unit_test(test_linebuffer_write_justified),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
