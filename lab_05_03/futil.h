#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define FILE_ERROR -3
#define IO_ERROR -4

int get_number_by_pos(FILE *file, int pos);
void set_number_by_pos(FILE *file, int pos, int num);
void fswap(FILE *f, int p1, int p2);
int fsize(FILE *file, int *ec);
int frcreate(FILE *file, int n);
int fprint(FILE *file);
int fsort(FILE *file);

#endif