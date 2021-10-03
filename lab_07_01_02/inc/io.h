#ifndef __IO_H__
#define __IO_H__ 

#include <stdio.h>

int n_numbers(FILE *f, int *ec);
void write_arr(int *arr, int n, FILE *f);
int *read_numbers(FILE *f, int *n, int *ec);

#endif // !__IO_H__