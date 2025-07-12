#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "linebuffer.h"
#include "word.h"

int justify(size_t linebuffer_capacity, FILE *in, FILE *out);

#define DEFAULT_LINEBUFFER_CAPACITY 72

void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s [-w WIDTH]\n", prog);
}

int main(int argc, char *argv[]) {
    int opt;
    int width;
    size_t linebuffer_capacity = DEFAULT_LINEBUFFER_CAPACITY;

    while ((opt = getopt(argc, argv, "w:h")) != -1) {
        switch (opt) {
            case 'w':
                width = atoi(optarg);
                if (width <= 0) {
                    print_usage(argv[0]);
                    return EXIT_FAILURE;
                }
                linebuffer_capacity = (size_t) width;
                break;
            case 'h':
                print_usage(argv[0]);
                return EXIT_SUCCESS;
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }
    return justify(linebuffer_capacity, stdin, stdout);
}

int justify(size_t linebuffer_capacity, FILE *in, FILE *out) {
    const size_t MAX_WORD_LENGTH = linebuffer_capacity;
    char word[MAX_WORD_LENGTH + 2];
    size_t word_length;
    int read_word_result;
    LineBuffer *lb = linebuffer_create(linebuffer_capacity);

    while ((read_word_result = read_word(in, word, MAX_WORD_LENGTH + 1)) ==
           READ_WORD_SUCCESS) {
        word_length = strlen(word);
        if (word_length == 0) {
            linebuffer_write(lb, out);
            linebuffer_destroy(lb);
            return EXIT_SUCCESS;
        }
        if (word_length > MAX_WORD_LENGTH) {
            // TODO: If the word is too long for a given line,
            // we should wrap it to the next line.
            word[MAX_WORD_LENGTH] = '*';
        }
        if (!linebuffer_append_word(lb, word)) {
            linebuffer_write_justified(lb, out);
            linebuffer_clear(lb);
            linebuffer_append_word(lb, word);
        }
        memset(word, 0, MAX_WORD_LENGTH + 2);
    }
    if (read_word_result == READ_WORD_ERR_READ) {
        fprintf(stderr, "Error reading word\n");
        return EXIT_FAILURE;
    }
    if (lb->_num_words > 0) {
        linebuffer_write(lb, out);
    }
    linebuffer_destroy(lb);
    return EXIT_SUCCESS;
}
