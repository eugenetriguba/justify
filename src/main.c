#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "linebuffer.h"
#include "word.h"

#define MAX_WORD_LENGTH 20
#define LINEBUFFER_CAPACITY 60

int main(void) {
    char word[MAX_WORD_LENGTH + 2];
    size_t word_length;
    int read_word_result;
    LineBuffer *lb = linebuffer_create(LINEBUFFER_CAPACITY);

    while ((read_word_result = read_word(stdin, word, MAX_WORD_LENGTH + 1)) ==
           READ_WORD_SUCCESS) {
        word_length = strlen(word);
        if (word_length == 0) {
            linebuffer_write(lb, stdout);
            linebuffer_destroy(lb);
            return 0;
        }
        if (word_length > MAX_WORD_LENGTH) {
            word[MAX_WORD_LENGTH] = '*';
        }
        if (word_length >= linebuffer_space_remaining(lb)) {
            linebuffer_write_justified(lb, stdout);
            linebuffer_clear(lb);
        }
        linebuffer_append_word(lb, word);
        memset(word, 0, MAX_WORD_LENGTH + 2);
    }
    if (read_word_result == READ_WORD_ERR_READ) {
        fprintf(stderr, "Error reading word\n");
        return 1;
    }
    return 0;
}
