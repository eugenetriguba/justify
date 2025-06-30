#ifndef WORD_H
#define WORD_H

#include <stdio.h>

#define READ_WORD_ERR_READ -1
#define READ_WORD_ERR_EOF 0
#define READ_WORD_SUCCESS 1

/**
 * Read in a word from a file up to size length.
 *
 * If there is any leading whitespace, it will be discarded
 * before starting to read in a word.
 *
 * @param[in] fp The file to read a word from.
 * @param[out] word The word that was read as a null-terminated string.
 * @param[in] length The length of the word to read in.
 *
 * @note `length` should be the number of characters you'd
 *       like to read in plus one to take into account the
 *       null terminator.
 *
 * @returns < 0 on read error; 0 on EOF; > 0 on success.
 */
int read_word(FILE *fp, char *word, size_t length);

#endif
