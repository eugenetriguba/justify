#include "word.h"

static int read_char(FILE *fp);

int read_word(FILE *fp, char *word, size_t length) {
    int ch;
    size_t position = 0;

    while ((ch = read_char(fp)) == ' ')
        ;

    while (ch != ' ' && ch != EOF) {
        if (position < length) {
            word[position++] = ch;
        }
        ch = read_char(fp);
    }
    word[position] = '\0';
    return ch;
}

static inline int read_char(FILE *fp) {
    int ch = getc(fp);
    if (ch == '\n' || ch == '\t') {
        return ' ';
    }
    return ch;
}
