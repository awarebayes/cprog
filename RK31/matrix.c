#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

matrix_t matrix_new(int n, int m)
{
    matrix_t self = {0};
    self.rows = n;
    self.cols = m;
    void *ptr = calloc(sizeof(int *) * n + sizeof(int) * m * n, sizeof(char));
    char *cptr = (char *)ptr;
    int **pa = (int**)cptr;
    int *data_ptr = (int*)(cptr + sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        *(pa + i) = data_ptr + m * i;
    self.data = pa;
    return self;
}

matrix_t matrix_copy(matrix_t *self)
{
	matrix_t copy = matrix_new(self->rows, self->cols);
    	for (int i = 0; i < self->rows; i++)
        	for (int j = 0; j < self->cols; j++)
			*(*(copy.data + i) + j) = *(*(self->data + i) + j);
	return copy;

}


void matrix_delete(matrix_t *self)
{
    free(self->data);
}

void matrix_print(matrix_t *self, FILE *fout)
{
    fprintf(fout, "%d %d\n", self->rows, self->cols);
    for (int i = 0; i < self->rows; i++)
    {
        for (int j = 0; j < self->cols; j++)
        {
            fprintf(fout, "%-4d", *(*(self->data +i ) + j));
        }
        fprintf(fout, "\n");
    }

}

matrix_t matrix_read(FILE *fin)
{
	int n = 0;
	fscanf(fin, "%d", &n);
	matrix_t self = matrix_new(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fscanf(fin, "%d",  *(self.data + i) + j);
	return self;
}


int matrix_get(matrix_t *self, int i, int j)
{
	while (i < 0)
		i += self->rows;
	while (j < 0)
		j += self->cols;
	i %= self->rows;
	j %= self->cols;
	return *(*(self->data + i) + j);
}

int matrix_equal(matrix_t *self, matrix_t *other)
{
	if (self->cols != other-> cols || self-> rows != other->rows)
		return 0;

	int flag = 1;
	for (int i = 0; i < self-> rows && flag; i++)
		for (int j = 0; j < self->cols && flag; j++)
			if (*(*(self->data + i) + j) != *(*(other->data + i) +j))
				flag = 0;
	return flag;
}

matrix_t life_update(matrix_t *self, int *ended)
{
	matrix_t copy = matrix_copy(self);
	int survived = 0;
	for (int i = 0; i < self->rows; i++)
		for (int j = 0; j < self->cols; j++)
		{
			int i_survived = 0;
			int i_alive = self->data[i][j];
			int neighbours = 0;

			// maybe there is self instead of copy
			neighbours += matrix_get(&copy, i-1, j); 
			neighbours += matrix_get(&copy, i+1, j); 
			neighbours += matrix_get(&copy, i, j-1); 
			neighbours += matrix_get(&copy, i, j+1); 
			if (i_alive == 0 && neighbours == 3)
				i_survived = 1;
			if (i_alive == 1 && (neighbours == 2 ||neighbours == 3))
				i_survived = 1;	
			
			survived += i_survived;
			copy.data[i][j] = i_survived;
		}
	if (survived == 0 || matrix_equal(self, &copy))
		*ended = 1;
	return copy;	
}

