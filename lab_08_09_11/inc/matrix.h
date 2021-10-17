#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>

typedef struct {
    int rows;
    int columns;
    double **data;
} matrix_t;

matrix_t matrix_new(int n, int m, int *ec);
matrix_t matrix_from_array(const double *arr, int n, int m, int *ec);
matrix_t matrix_from_file(FILE *fin, int *ec);
void matrix_delete(matrix_t *self);
void matrix_print(matrix_t *self, FILE *fout);
matrix_t matrix_add(matrix_t *self, matrix_t *other, int *ec);
matrix_t matrix_mul(matrix_t *self, matrix_t *other, int *ec);
matrix_t gaussian_solve(matrix_t *self, int *ec);
int matrix_eq(matrix_t *self, matrix_t *other);

#endif // !__MATRIX_H__
