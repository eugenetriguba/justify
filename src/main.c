#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "linebuffer.h"
#include "word.h"

#define DEFAULT_LINEBUFFER_CAPACITY 72

void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s [-w WIDTH]\n", prog);
}

int main(int argc, char *argv[]) {
    int opt;
    size_t linebuffer_capacity = DEFAULT_LINEBUFFER_CAPACITY;

    while ((opt = getopt(argc, argv, "w:h")) != -1) {
        switch (opt) {
            case 'w':
                linebuffer_capacity = (size_t)atoi(optarg);
                if (linebuffer_capacity == 0) {
                    print_usage(argv[0]);
                    return EXIT_FAILURE;
                }
                break;
            case 'h':
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    const size_t MAX_WORD_LENGTH = linebuffer_capacity;
    // Use a larger buffer to read complete words, even if they're longer than line capacity
    const size_t WORD_BUFFER_SIZE = MAX_WORD_LENGTH * 4; // Allow for very long words
    char word[WORD_BUFFER_SIZE + 2];
    size_t word_length;
    int read_word_result;
    LineBuffer *lb = linebuffer_create(linebuffer_capacity);

    while ((read_word_result = read_word(stdin, word, WORD_BUFFER_SIZE + 1)) ==
           READ_WORD_SUCCESS) {
        word_length = strlen(word);
        if (word_length == 0) {
            linebuffer_write(lb, stdout);
            linebuffer_destroy(lb);
            return EXIT_SUCCESS;
        }
        
        // Handle words longer than the line buffer by breaking them into chunks
        if (word_length > MAX_WORD_LENGTH) {
            size_t word_pos = 0;
            while (word_pos < word_length) {
                size_t remaining_word = word_length - word_pos;
                size_t space_available = linebuffer_space_remaining(lb);
                size_t chunk_size;
                
                // If we have words in the buffer, we need space for a preceding space
                if (lb->_num_words > 0) {
                    if (space_available <= 1) {
                        // Not enough space even for a space, flush the buffer
                        linebuffer_write_justified(lb, stdout);
                        linebuffer_clear(lb);
                        space_available = linebuffer_space_remaining(lb);
                    } else {
                        space_available--; // Reserve space for the preceding space
                    }
                }
                
                // Determine chunk size: either remaining space or remaining word, whichever is smaller
                chunk_size = (remaining_word < space_available) ? remaining_word : space_available;
                if (chunk_size == 0) {
                    chunk_size = (remaining_word < MAX_WORD_LENGTH) ? remaining_word : MAX_WORD_LENGTH;
                }
                
                // Create a chunk from the word
                char chunk[WORD_BUFFER_SIZE + 2];
                memset(chunk, 0, WORD_BUFFER_SIZE + 2);
                strncpy(chunk, word + word_pos, chunk_size);
                chunk[chunk_size] = '\0';
                
                // Try to append the chunk
                if (!linebuffer_append_word(lb, chunk)) {
                    linebuffer_write_justified(lb, stdout);
                    linebuffer_clear(lb);
                    linebuffer_append_word(lb, chunk);
                }
                
                word_pos += chunk_size;
            }
        } else {
            // Handle normal-sized words
            if (!linebuffer_append_word(lb, word)) {
                linebuffer_write_justified(lb, stdout);
                linebuffer_clear(lb);
                linebuffer_append_word(lb, word);
            }
        }
        memset(word, 0, WORD_BUFFER_SIZE + 2);
    }
    if (read_word_result == READ_WORD_ERR_READ) {
        fprintf(stderr, "Error reading word\n");
        return EXIT_FAILURE;
    }
    if (lb->_num_words > 0) {
        linebuffer_write(lb, stdout);
    }
    linebuffer_destroy(lb);
    return EXIT_SUCCESS;
}
