#include "word.h"

#include <ctype.h>

int read_word(FILE *fp, char *word, size_t length) {
    if (fp == NULL || word == NULL) {
        return READ_WORD_ERR_READ;
    }

    int ch;
    size_t position = 0;

    while (isspace(ch = getc(fp)))
        ;

    while (!isspace(ch) && ch != EOF) {
        if (position >= length - 1) {
            // Note: -1 to ensure we have space for the null terminator
            // Once we hit the end of our available space, we stop reading,
            // even if we didn't read the whole word.
            break;
        }
        word[position++] = ch;
        ch = getc(fp);
    }
    if (length >= 0) {
        word[position] = '\0';
    }

    if (ferror(fp)) {
        return READ_WORD_ERR_READ;
    }
    if (position == 0 && ch == EOF) {
        return READ_WORD_ERR_EOF;
    }
    return READ_WORD_SUCCESS;
}
