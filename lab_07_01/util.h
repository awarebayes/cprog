#ifndef  _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

enum ec {
    ok, 
    arg_err,
    read_err,
    malloc_err,
};

int key(const int *pb_src, const int *pe_src, const int **pb_dst, int **pe_dst);
int *read_numbers(FILE *f, int *n, int *ec);
void print_arr(int *arr, int n);

#endif // ! _UTIL_H_