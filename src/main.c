#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "linebuffer.h"
#include "word.h"

int justify(size_t line_width, FILE *in, FILE *out);

#define DEFAULT_LINE_WIDTH 72

void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s [-w WIDTH]\n", prog);
}

int main(int argc, char *argv[]) {
    int opt;
    int width = DEFAULT_LINE_WIDTH;

    while ((opt = getopt(argc, argv, "w:h")) != -1) {
        switch (opt) {
            case 'w':
                width = atoi(optarg);
                if (width <= 0) {
                    print_usage(argv[0]);
                    return EXIT_FAILURE;
                }
                break;
            case 'h':
                print_usage(argv[0]);
                return EXIT_SUCCESS;
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }
    return justify((size_t) width, stdin, stdout);
}

int justify(size_t line_width, FILE *in, FILE *out) {
    const size_t MAX_WORD_LENGTH = line_width;
    char word[MAX_WORD_LENGTH + 1];
    size_t word_length;
    int read_word_result;
    LineBuffer *lb = linebuffer_create(line_width);
    if (lb == NULL) {
        fprintf(stderr, "An error occurred while allocating memory for a line buffer\n");
        return EXIT_FAILURE;
    }

    read_word_result = read_word(in, word, MAX_WORD_LENGTH + 1);
    while (read_word_result == READ_WORD_SUCCESS) {
        if (!linebuffer_append_word(lb, word)) {
            linebuffer_write_justified(lb, out);
            linebuffer_clear(lb);
            linebuffer_append_word(lb, word);
        }
        read_word_result = read_word(in, word, MAX_WORD_LENGTH + 1);
    }
    if (read_word_result == READ_WORD_ERR_READ) {
        fprintf(stderr, "An error occurred while attempting to read in a word\n");
        linebuffer_destroy(lb);
        return EXIT_FAILURE;
    }
    if (linebuffer_space_remaining(lb) < line_width) {
        linebuffer_write(lb, out);
    }
    linebuffer_destroy(lb);
    return EXIT_SUCCESS;
}
