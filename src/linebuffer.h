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
 * @brief Create a new LineBuffer
 *
 * @param line_length The length of the buffer to use.
 *
 * @returns The newly allocated LineBuffer; otherwise NULL
 *          if the allocation fails.
 */
LineBuffer *linebuffer_create(size_t line_length);

/**
 * @brief Release any allocated memory for the LineBuffer
 *
 * @param lb The LineBuffer to destroy.
 */
void linebuffer_destroy(LineBuffer *lb);

/**
 * @brief Clear the current buffer
 *
 * @param lb The LineBuffer to clear.
 */
void linebuffer_clear(LineBuffer *lb);

/**
 * @brief Append a word to the end of the buffer.
 *
 * @param lb The line buffer to append to.
 * @param word The word to append.
 */
void linebuffer_append_word(LineBuffer *lb, const char *word);

/**
 * @brief Check how many characters can be added.
 *
 * @param lb The line buffer to check the space of.
 *
 * @returns The number of characters left in the line.
 */
size_t linebuffer_space_remaining(LineBuffer *lb);

/**
 * @brief Write the current line.
 *
 * @param lb The line buffer to read.
 * @param fp The file to write out the line buffer to.
 *
 * @returns >= 0 on success; EOF on error.
 */
int linebuffer_write(LineBuffer *lb, FILE *fp);

/**
 * @brief Write the current line as justified text.
 *
 * @param lb The line buffer to read.
 * @param fp The file to write out the line buffer to.
 *
 * @returns >= 0 on success; EOF on error.
 */
int linebuffer_write_justified(LineBuffer *lb, FILE *fp);

#endif
