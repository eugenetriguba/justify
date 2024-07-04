#include "linebuffer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strlcat.h"

LineBuffer *linebuffer_create(size_t buffer_capacity) {
    LineBuffer *lb = malloc(sizeof(LineBuffer));
    if (lb == NULL) {
        return NULL;
    }
    lb->_buffer = malloc(buffer_capacity + 1);
    if (lb->_buffer == NULL) {
        free(lb);
        return NULL;
    }
    memset(lb->_buffer, 0, buffer_capacity + 1);
    lb->_num_words = 0;
    lb->_buffer_length = 0;
    lb->_buffer_capacity = buffer_capacity;
    return lb;
}

void linebuffer_destroy(LineBuffer *lb) {
    free(lb->_buffer);
    free(lb);
}

void linebuffer_clear(LineBuffer *lb) {
    memset(lb->_buffer, 0, lb->_buffer_capacity + 1);
    lb->_num_words = 0;
    lb->_buffer_length = 0;
}

void linebuffer_append_word(LineBuffer *lb, const char *word) {
    if (lb->_num_words > 0) {
        lb->_buffer[lb->_buffer_length] = ' ';
        lb->_buffer[lb->_buffer_length + 1] = '\0';
        lb->_buffer_length++;
    }
    strlcat(lb->_buffer, word, (lb->_buffer_capacity + 1) - lb->_buffer_length);
    lb->_buffer_length += strlen(word);
    lb->_num_words++;
}

size_t linebuffer_space_remaining(LineBuffer *lb) {
    return lb->_buffer_capacity - lb->_buffer_length;
}

int linebuffer_write(LineBuffer *lb, FILE *fp) {
    if (lb->_buffer_length > 0) {
        return fputs(lb->_buffer, fp);
    }
    return 0;
}

int linebuffer_write_justified(LineBuffer *lb, FILE *fp) {
    int return_code = 0;
    size_t words_remaining = lb->_num_words;
    size_t extra_spaces = linebuffer_space_remaining(lb);
    size_t spaces_to_insert = 0;

    for (size_t i = 0; i < lb->_buffer_length; i++) {
        if (!isspace(lb->_buffer[i])) {
            return_code = fputc(lb->_buffer[i], fp);
            if (return_code == EOF) {
                return EOF;
            }
        } else {
            spaces_to_insert = extra_spaces / (words_remaining - 1);
            extra_spaces -= spaces_to_insert;
            for (size_t j = 1; j <= spaces_to_insert + 1; j++) {
                return_code = fputc(' ', fp);
                if (return_code == EOF) {
                    return EOF;
                }
            }
            words_remaining--;
        }
    }
    return_code = fputc('\n', fp);
    if (return_code == EOF) {
        return EOF;
    }
    return return_code;
}
