#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <stdio.h>

#define MWORDLEN 16
#define MWORDS 128
#define MSTRLEN 256
#define DELIM " ,;:-.!?"

int split_string_to_words(char **words, char *str);
int delete_matching_last_word(char **words, int n);
void delete_letters_matching_first(char *word);
void solve(int n_words, char **pa, char *end);
int max_word_len(char *str);

#endif // _STRINGS_