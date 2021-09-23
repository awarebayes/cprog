#ifndef  _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

enum ec 
{
    ok, 
    arg_err,
    read_err,
    malloc_err,
    path_err,
    empty_arr_err,
};

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
int *read_numbers(FILE *f, int *n, int *ec);
int n_numbers(FILE *f, int *ec);
void write_arr(int *arr, int n, FILE *f);
void mysort(void *base, size_t nitems, size_t size, int (*cmp)(const void *, const void *));
int int_cmp(const void *a, const void *b);

#endif // _UTIL_H_