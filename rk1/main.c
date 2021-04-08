// Написал Щербина МА ИУ7 25 Б
// VAR 2

#include <stdio.h>
#define N 10

enum error_code
{
	ok,
	input_error
};

int read_mat(int *n, int *m, int (*mat)[N]);
void print_mat(int n, int m, int (*mat)[N]);
void get_mins(int n, int m, int (*mat)[N], int (*mins)[N]);
void sort_arr(int n, int (*arr)[N]);
void print_arr(int n, int *arr);
void print_err(int ec);

int main()
{
	int mat[N][N];
	int n, m;
	int ec = ok;
	int mins[N];

	ec = read_mat(&n, &m, mat);
	if (!ec)
	{
		print_mat(n, m, mat);
		get_mins(n, m, mat, &mins);
		sort_arr(n, &mins);
		printf("Arr:\n");
		print_arr(n, mins);
	}
	print_err(ec);

}

int read_mat(int *n, int *m, int (*mat)[N])
{
	printf(">>> n, m:\n");
	if (scanf("%d %d", n, m) != 2)
		return input_error;

	if ((*n) > N || *n < 0 || *m > N || *m < 0 )
		return input_error;

	// todo check n, m
	for (int i = 0; i < *n; i++)
	{
		for (int j = 0; j < *m; j++)
		{
			// todo error check
			if (scanf("%d", &mat[i][j]) != 1)
				return input_error;
		}
	}
	return ok;
}

void print_mat(int n, int m, int (*mat)[N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", mat[i][j]); 
		}
		printf("\n");
	}
}

void get_mins(int n, int m, int (*mat)[N], int (*mins)[N])
{
	for (int c = 0; c < m; c++)
	{

		int min = mat[0][c];
		for (int r = 0; r < n; r++)
		{
			if (mat[r][c] < min)
			{
				min = mat[r][c];
			}
		}
		(*mins)[c] = min;

	}
}

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}


void sort_arr(int n, int (*arr)[N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n-1; j++)
		{
			if ((*arr)[j] > (*arr)[j+1])
			{
				int t = (*arr)[j];
				(*arr)[j] = (*arr)[j+1];
				(*arr)[j+1] = t;
				// Запутался с указателями((((0(
				// swap(arr[j], arr[j+1]);
			}
		}
	}
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

