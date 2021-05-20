#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

#define ARG_ERROR -1
#define NO_FILE_EXISTS -2
#define NO_POS -3

void create_random_file(char *filename, int n);
int print_file(char *filename);
int get_number_by_pos(FILE *file, int pos, int *ec);

#endif