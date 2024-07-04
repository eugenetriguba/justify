#include "linebuffer.h"
#include "word.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 20

int main(void) {
    char word[MAX_WORD_LENGTH + 2];
    size_t word_length;
    int err;
    LineBuffer *lb = linebuffer_create(40);

    while (true) {
        err = read_word(stdin, word, MAX_WORD_LENGTH + 1);
        if (err == EOF) {
            printf("Error reading word\n");
            return 1;
        }
        word_length = strlen(word);
        if (word_length == 0) {
            linebuffer_write(lb, stdout);
            return 0;
        }
        if (word_length > MAX_WORD_LENGTH) {
            word[MAX_WORD_LENGTH] = '*';
        }
        if (word_length + 1 > linebuffer_space_remaining(lb)) {
            linebuffer_write_justified(lb, stdout);
            linebuffer_clear(lb);
        }
        linebuffer_append_word(lb, word);
    }
}
