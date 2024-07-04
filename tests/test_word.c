#include "word.h"
// clang-format off
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
// clang-format on
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *create_tmp_file(const char *data) {
    FILE *fp = tmpfile();
    assert_non_null(fp);
    fprintf(fp, "%s", data);
    rewind(fp);
    return fp;
}

void test_read_word_simple(void **state) {
    const char *input = "hello";
    const char *expected = "hello";
    FILE *fp = create_tmp_file(input);

    char word[100];
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    fclose(fp);
}

void test_read_word_leading_spaces(void **state) {
    const char *input = "  leading";
    const char *expected = "leading";
    FILE *fp = create_tmp_file(input);

    char word[100];
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    fclose(fp);
}

void test_read_word_trailing_spaces(void **state) {
    const char *input = "trailing  ";
    const char *expected = "trailing";
    FILE *fp = create_tmp_file(input);

    char word[100];
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    fclose(fp);
}

void test_read_word_multiple_spaces(void **state) {
    const char *input = "multiple   spaces";
    const char *expected = "multiple";
    FILE *fp = create_tmp_file(input);

    char word[100];
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    fclose(fp);
}

void test_read_word_single_word(void **state) {
    const char *input = "singleword";
    const char *expected = "singleword";
    FILE *fp = create_tmp_file(input);

    char word[100];
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    fclose(fp);
}

void test_read_word_empty_input(void **state) {
    const char *input = "";
    const char *expected = "";
    FILE *fp = create_tmp_file(input);

    char word[100];
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_ERR_EOF);
    assert_string_equal(word, expected);

    fclose(fp);
}

void test_read_word_null_fp(void **state) {
    char word[100];
    int result = read_word(NULL, word, sizeof(word));
    assert_int_equal(result, READ_WORD_ERR_READ);
}

void test_read_word_null_word(void **state) {
    FILE *fp = tmpfile();
    assert_non_null(fp);

    int result = read_word(fp, NULL, 100);
    assert_int_equal(result, READ_WORD_ERR_READ);

    fclose(fp);
}

void test_read_word_zero_length(void **state) {
    FILE *fp = tmpfile();
    assert_non_null(fp);

    char word[100];
    int result = read_word(fp, word, 0);
    assert_int_equal(result, READ_WORD_ERR_EOF);

    fclose(fp);
}

void test_read_word_buffer_overflow(void **state) {
    const char *input = "thisisaverylongword";
    const char *expected = "thisisaver";
    FILE *fp = create_tmp_file(input);

    char word[11];  // Buffer size is 11 including null terminator
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    fclose(fp);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_read_word_simple),
        cmocka_unit_test(test_read_word_leading_spaces),
        cmocka_unit_test(test_read_word_trailing_spaces),
        cmocka_unit_test(test_read_word_multiple_spaces),
        cmocka_unit_test(test_read_word_single_word),
        cmocka_unit_test(test_read_word_empty_input),
        cmocka_unit_test(test_read_word_null_fp),
        cmocka_unit_test(test_read_word_null_word),
        cmocka_unit_test(test_read_word_zero_length),
        cmocka_unit_test(test_read_word_buffer_overflow),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}