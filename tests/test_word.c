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

/**
 * GIVEN the an input containing a single word
 * WHEN we read a word from the file
 * THEN we would expect to read in the single word
 */
void test_read_word_single_word(void **state) {
    const char *input = "hello";
    const char *expected = "hello";
    FILE *fp = create_tmp_file(input);
    char word[100];

    int result = read_word(fp, word, sizeof(word));

    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);
    fclose(fp);
}

/**
 * GIVEN an input string with leading spaces
 * WHEN we read a word from the file
 * THEN we would expect to have discarded the leading spaces and
 *      read in the following word
 */
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

/**
 * GIVEN an input string with trailing spaces
 * WHEN we read a word from the file
 * THEN we would expect to read in the word without
 *   the trailing spaces
 * WHEN we read in another word
 * THEN we expect to see the remaining spaces simply get
 *   consumed and get back EOF
 */
void test_read_word_trailing_spaces(void **state) {
    const char *input = "trailing  ";
    const char *expected = "trailing";
    FILE *fp = create_tmp_file(input);
    char word[100];

    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_ERR_EOF);
    assert_string_equal(word, "");

    fclose(fp);
}

/**
 * GIVEN an input string with multiple spaces between words
 * WHEN we read a word from the file
 * THEN we expect to read in the first word
 * WHEN we read in another word from the file
 * THEN we expect to skip over the multiple spaces
 *   and read in the last word
 */
void test_read_word_multiple_spaces(void **state) {
    const char *input = "multiple   spaces";
    FILE *fp = create_tmp_file(input);
    char word[100];

    char *expected = "multiple";
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    expected = "spaces";
    result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected); 

    fclose(fp);
}

/**
 * GIVEN an empty input string
 * WHEN we read a word from the file
 * THEN we expect to get EOF on read
 */
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

/**
 * GIVEN an input string that is only whitespace characters
 * WHEN we read a word from the file
 * THEN we expect to get EOF on read
 */
void test_read_word_input_with_only_spaces(void **state) {
    const char *input = "   \t\t\n\n";
    const char *expected = "";
    FILE *fp = create_tmp_file(input);
    char word[100];

    int result = read_word(fp, word, sizeof(word));

    assert_int_equal(result, READ_WORD_ERR_EOF);
    assert_string_equal(word, expected);
    fclose(fp);
}

/**
 * GIVEN a NULL input
 * WHEN we read a word from the file
 * THEN we expect to get a read error
 */
void test_read_word_null_fp(void **state) {
    char word[100];
    int result = read_word(NULL, word, sizeof(word));
    assert_int_equal(result, READ_WORD_ERR_READ);
}

/**
 * GIVEN a NULL word buffer
 * WHEN we read a word from the file
 * THEN we expect to get a read error
 */
void test_read_word_null_word(void **state) {
    FILE *fp = tmpfile();
    assert_non_null(fp);

    int result = read_word(fp, NULL, 100);

    assert_int_equal(result, READ_WORD_ERR_READ);
    fclose(fp);
}

/**
 * GIVEN a word buffer with a 0 length
 * WHEN we read a word from the file
 * THEN we expect to get EOF
 */
void test_read_word_zero_length(void **state) {
    FILE *fp = tmpfile();
    assert_non_null(fp);
    char word[100];

    int result = read_word(fp, word, 0);

    assert_int_equal(result, READ_WORD_ERR_EOF);
    fclose(fp);
}

/**
 * GIVEN a word that is too long to fit into the word buffer
 * WHEN we read a word from the file
 * THEN we expect to get the partial word back
 * WHEN we read in another word
 * THEN we expect to get the remainder of the word
 */
void test_read_word_overflow(void **state) {
    const char *input = "thisisaverylongword";
    FILE *fp = create_tmp_file(input);
    char word[11];  // Buffer size is 11 to include null terminator

    char *expected = "thisisaver";
    int result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    expected = "ylongword";
    result = read_word(fp, word, sizeof(word));
    assert_int_equal(result, READ_WORD_SUCCESS);
    assert_string_equal(word, expected);

    fclose(fp);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_read_word_single_word),
        cmocka_unit_test(test_read_word_leading_spaces),
        cmocka_unit_test(test_read_word_trailing_spaces),
        cmocka_unit_test(test_read_word_multiple_spaces),
        cmocka_unit_test(test_read_word_empty_input),
        cmocka_unit_test(test_read_word_input_with_only_spaces),
        cmocka_unit_test(test_read_word_null_fp),
        cmocka_unit_test(test_read_word_null_word),
        cmocka_unit_test(test_read_word_zero_length),
        cmocka_unit_test(test_read_word_overflow),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
