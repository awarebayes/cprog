#ifndef _COUNT_H_
#define _COUNT_H_

#define MSLEN 256 // MaxStringLen
#define MWORDS 128 // MaxWords in string
#define MWORDLEN 16 // MaxWordLen

void print_word_count(char **pa, int n_words);
void unique_words(char **pa, char **unique, int n_words, int *n_unique);
void word_count(char **pa, char **unique, int *count, int n_words, int n_unique);

#endif
