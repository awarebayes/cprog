#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

int fget(FILE *file, int pos);
void fset(FILE *file, int pos, int num);
void fswap(FILE *f, int p1, int p2);
int fsize(FILE *file);
void frcreate(char *filename, int n);
void fprint(char *filename);
void fsort(char *filename);

#endif