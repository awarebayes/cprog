#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <time.h>


#define NO_FILE -3

int get_number_by_pos(FILE *file, int pos);
void set_number_by_pos(FILE *file, int pos, int num);
void fswap(FILE *f, int p1, int p2);
int fsize(FILE *file);
void frcreate(char *filename, int n);
int fprint(char *filename);
int fsort(char *filename);

#endif