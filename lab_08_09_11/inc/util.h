#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>

#define BUF_SIZE 4096
#define PREC 0.0001

enum enum_err
{
	ok,
	input_err,
	file_err,
	malloc_err,
	matrix_size_err,
	math_error,
	arg_err,
};

double *read_arr(FILE *fin, int n, int *ec);

int fcmp(double f1, double f2);

void arr_mul(double by, double *arr, int n);

void arr_sub(double *from, const double *what, int n);

#endif // !__UTIL_H__
