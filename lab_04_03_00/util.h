#ifndef _UTIL_H_
#define _UTIL_H_

enum ec
{
    ok,
    no_words,
    string_overflow,
    long_word,
    no_words_remaining
};

#include <stdio.h>
void transform(size_t n, size_t m, char *mat, char **pa);
void print_error(const int ec);
int read_line(char *s, int n, int *ec);

#endif // _UTIL_H_