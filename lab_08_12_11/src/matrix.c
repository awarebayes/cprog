#include "matrix.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

matrix_t matrix_new(int n, int m, int *ec)
{
	matrix_t self = { 0 };
	self.rows = n;
	self.columns = m;
	self.data = calloc(self.rows, sizeof(double *));
	if (self.data == NULL && ec != NULL)
		*ec = malloc_err;
	if (!*ec)
	{
		for (int i = 0; i < n; i++)
		{
			self.data[i] = calloc(self.columns, sizeof(double));
			if (self.data[i] == NULL)
				*ec = malloc_err;
		}
	}
	if (*ec)
		matrix_delete(&self);
	return self;
}

matrix_t matrix_from_matrix(const matrix_t *m, int *ec)
{
	matrix_t self = matrix_new(m->rows, m->columns, ec);
	for (int i = 0; i < m->rows; i++)
		for (int j = 0; j < m->columns; j++)
			self.data[i][j] = m->data[i][j];
	return self;
}

void matrix_delete(matrix_t *self)
{
	for (int i = 0; i < self->rows; i++)
	{
		free(self->data[i]);
		self->data[i] = NULL;
	}
	free(self->data);
	self->data = NULL;
}

matrix_t matrix_from_array(const double *arr, int n, int m, int *ec)
{
	matrix_t self = matrix_new(n, m, ec);
	self.rows = n;
	self.columns = m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			self.data[i][j] = arr[j + i * m];
	return self;
}

matrix_t matrix_from_file(FILE *fin, int *ec)
{
	int n = 0, m = 0;
	if (fscanf(fin, "%d %d", &n, &m) != 2)
		*ec = input_err;
	if (m <= 0 || n <= 0)
		*ec = input_err;
	double *arr = read_arr(fin, m * n, ec);
	matrix_t self = { 0 };
	if (!*ec)
		self = matrix_from_array(arr, n, m, ec);
	free(arr);
	return self;
}

void matrix_print(const matrix_t *self, FILE *fout)
{
	fprintf(fout, "%d %d\n", self->rows, self->columns);
	for (int i = 0; i < self->rows; i++)
	{
		for (int j = 0; j < self->columns; j++)
			fprintf(fout, "%.6lf ", self->data[i][j]);
		fprintf(fout, "\n");
	}
}

matrix_t matrix_add(matrix_t *self, matrix_t *other, int *ec)
{
	matrix_t res = { 0 };
	if (self->rows != other->rows || self->columns != other->columns)
	{
		*ec = matrix_size_err;
		return res;
	}
	if (!*ec)
	{
		res = matrix_new(self->rows, self->columns, ec);
		for (int i = 0; i < self->rows; ++i)
			for (int j = 0; j < self->columns; ++j)
				res.data[i][j] = self->data[i][j] + other->data[i][j];
	}
	return res;
}


matrix_t matrix_mul(matrix_t *self, matrix_t *other, int *ec)
{
	matrix_t res = { 0 };
	if (self->columns != other->rows)
		*ec = matrix_size_err;
	if (*ec)
		return res;

	res = matrix_new(self->rows, other->columns, ec);
	for (int i = 0; i < self->rows; ++i)
		for (int j = 0; j < other->columns; ++j)
			for (int k = 0; k < other->rows; ++k)
				res.data[i][j] += self->data[i][k] * other->data[k][j];
	return res;
}

void gaussian_elimination(matrix_t *self, int *ec)
{
	int n = self->rows;
	int m = self->columns;
	double **arr = self->data;
	for (int i = 0; i < n - 1; i++)
	{
		for (int k = i + 1; k < n; k++)
		{
			// Partial pivoting
			if (fabs(arr[i][i]) < fabs(arr[k][i]))
			{
				double *temp = arr[i];
				arr[i] = arr[k];
				arr[k] = temp;
			}
		}
		if (fcmp(arr[i][i], 0.0) == 0)
			*ec = math_error;
		if (!*ec)
		{
			// Begin elimination
			for (int k = i + 1; k < n; k++)
			{
				double term = arr[k][i] / arr[i][i];
				for (int j = 0; j < m; ++j)
					arr[k][j] = arr[k][j] - term * arr[i][j];
			}
		}
	}
}

double matrix_determinant(const matrix_t *self, int *ec)
{
	matrix_t matrix_copy = { 0 };
	double result = 1;
	int ec_elim = 0; // local error code for elimination results

	if (self->rows != self->columns)
		*ec = math_error;
	if (!*ec)
		matrix_copy = matrix_from_matrix(self, ec);
	if (!*ec)
		gaussian_elimination(&matrix_copy, &ec_elim);

	if (ec_elim != ok)
	{
		if (ec_elim == math_error)
			result = 0;
		else
			*ec = ec_elim;
	}

	if (!*ec)
	{
		for (int i = 0; i < self->rows; i++)
		{
			result *= matrix_copy.data[i][i];
		}
	}
	matrix_delete(&matrix_copy);
	return result;
}

int matrix_eq(matrix_t *self, matrix_t *other)
{
	int res = 1;
	if (self->rows != other->rows)
		res = 0;
	if (self->columns != other->columns)
		res = 0;
	for (int i = 0; i < self->rows && res; ++i)
	{
		for (int j = 0; j < self->columns && res; ++j)
		{
			if (fcmp(self->data[i][j], other->data[i][j]) != 0)
				res = 0;
		}
	}
	return res;
}
