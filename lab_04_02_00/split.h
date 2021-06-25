#ifndef _SPLIT_H_
#define _SPLIT_H_

#include <stdio.h>

int split(char **words, char *s, int n, int *ec);
void transform(size_t n, size_t m, char *mat, char **pa);

#endif