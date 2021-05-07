#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

enum ec
{
    ok,
    string_overflow,
    empty_string,
    input_error,
};

void transform(size_t n, size_t m, char *mat, char **pa);
char *strstrip(char *s);
int char_to_int(char c);

#endif // _UTIL_H_