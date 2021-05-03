#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

enum ec
{
    ok,
    string_overflow,
};

void transform(size_t n, size_t m, char *mat, char **pa);
void print_error(const int ec);
int read_line(char *s, int n, int *ec);

#endif // _UTIL_H_