#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
typedef struct
{
	int rows;
	int cols;
	int **data;
} matrix_t;

matrix_t matrix_new(int rows, int columns);
void matrix_delete(matrix_t *self);
matrix_t matrix_read(FILE *f);
void matrix_print(matrix_t *self, FILE*f);
matrix_t life_update(matrix_t *self, int *ended);

#endif
