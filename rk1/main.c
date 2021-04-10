// Написал Щербина МА ИУ7 25 Б
// VAR 2

#include <stdio.h>
#define N 10
#define M 10

enum error_code
{
	ok,
	input_error
};

void get_mins(int n, int m, int **ptr, int *mins);
void sort_arr(int n, int *arr);
void print_arr(int n, int *arr);
void print_err(int ec);
void transform(int n, int m, int *buf, int **mat);
int read_mat(int *n, int *m, int **ptrs);
void print_mat(int n, int m, int **ptr);

int main()
{
	int mat[N][M];
	int n, m;
	int ec = ok;
	int mins[N];
	int *ptr[N];
	transform(N, M, *mat, ptr);

	ec = read_mat(&n, &m, ptr);
	if (!ec)
	{
		print_mat(n, m, ptr);
		get_mins(n, m, ptr, mins);
		sort_arr(n, mins);
		printf("Arr:\n");
		print_arr(n, mins);
	}
	print_err(ec);
}

int read_mat(int *n, int *m, int **ptrs)
{
	printf(">>> n, m:\n");
	if (scanf("%d %d", n, m) != 2)
		return input_error;

	if ((*n) > N || *n < 0 || *m > N || *m < 0)
		return input_error;

	// todo check n, m
	for (int i = 0; i < *n; i++)
	{
		for (int j = 0; j < *m; j++)
		{
			// todo error check
			if (scanf("%d", ptrs[i] + j) != 1)
				return input_error;
		}
	}
	return ok;
}

void print_mat(int n, int m, int **ptr)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", ptr[i][j]);
		}
		printf("\n");
	}
}

void get_mins(int n, int m, int **ptr, int *mins)
{
	for (int c = 0; c < m; c++)
	{

		int min = ptr[0][c];
		for (int r = 0; r < n; r++)
		{
			if (ptr[r][c] < min)
			{
				min = ptr[r][c];
			}
		}
		mins[c] = min;
	}
}

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void print_arr(int n, int *arr)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void print_err(int ec)
{
	switch (ec)
	{
	case ok:
		break;
	case input_error:
		printf("Input Error");
		break;
	}
}

void transform(int n, int m, int *mat, int **ptr)
{
	for (int i = 0; i < n; i++)
		*(ptr + i) = mat + i * m;
}

void sort_arr(int n, int *arr)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				swap(arr + j, arr + j + 1);
			}
		}
	}
}

