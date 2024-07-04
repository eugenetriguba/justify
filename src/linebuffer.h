#ifndef LINEBUFFER_H
#define LINEBUFFER_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t _num_words;
    size_t _buffer_length;
    size_t _buffer_capacity;
    char *_buffer;
} LineBuffer;

/**
 * Create a new LineBuffer
 *
 * Args:
 *   line_length: The length of the buffer to use.
 *
 * Returns:
 *   The newly allocated LineBuffer; otherwise NULL
 *   if the allocation fails.
 */
LineBuffer *linebuffer_create(size_t line_length);

/**
 * Release any allocated memory for the LineBuffer
 *
 * Args:
 *   lb: The LineBuffer to destroy.
 */
void linebuffer_destroy(LineBuffer *lb);

/**
 * Clear the current buffer
 *
 * Args:
 *   lb: The LineBuffer to clear.
 */
void linebuffer_clear(LineBuffer *lb);

/**
 * Append a word to the end of the buffer.
 *
 * Args:
 *   lb: The line buffer to append to.
 *   word: The word to append.
 */
void linebuffer_append_word(LineBuffer *lb, const char *word);

/**
 * Check how many characters can be added.
 *
 * Args:
 *   lb: The line buffer to check the space of.
 *
 * Returns:
 *   The number of characters left in the line.
 */
size_t linebuffer_space_remaining(LineBuffer *lb);

/**
 * Write the current line.
 *
 * Args:
 *   lb: The line buffer to read.
 *   fp: The file to write out the line buffer to.
 *
 * Returns:
 *   >= 0 on success; EOF on error.
 */
int linebuffer_write(LineBuffer *lb, FILE *fp);

/**
 * Write the current line as justified text.
 *
 * Args:
 *   lb: The line buffer to read.
 *   fp: The file to write out the line buffer to.
 *
 * Returns:
 *   >= 0 on success; EOF on error.
 */
int linebuffer_write_justified(LineBuffer *lb, FILE *fp);

#endif
