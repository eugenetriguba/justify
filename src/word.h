#ifndef WORD_H
#define WORD_H

#include <stdio.h>

/**
 * Read in a word from a file up to size length.
 *
 * @param fp[in] The file to read a word from.
 * @param word[out] The word that was read as a null-terminated string.
 * @param length[in] The length of the word to read in.
 *
 * @note `length` should be the number of characters you'd
 *       like to read in plus one to take into account the
 *       null terminator.
 */
int read_word(FILE *fp, char *word, size_t length);

#endif
