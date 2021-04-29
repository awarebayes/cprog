/*
 * 2.3
 * Упорядочить строки матрицы:
 * 0. по возрастанию суммы их элементов;
 * Задача 2 лабы 3
 * Написал: Щербина Михаил
 */

#include <stdio.h>

#define N 10
#define M 10

enum error_code
{
    ok,
    input_error,
};

int validate_dim(size_t dim);
int input_mat(size_t *n, size_t *m, int **pa);
void print_mat(size_t n, size_t m, int **pa);
void print_error(int ec);
void bubble_sort(size_t len, int *values, int **pa, size_t m);
int row_sum(size_t row, size_t m, int **pa);
void swap_rows(size_t m, int *row1, int *row2);
void transform(size_t n, size_t m, int *mat, int **pa);

int main()
{
    int mat[N][N];
    int *pa[N];
    size_t m, n;

    int row_sums[N];
    transform(N, M, *mat, pa);

    int ec = ok;
    ec = input_mat(&n, &m, pa);
    if (!ec)
    {
        for (size_t i = 0; i < n; i++)
            row_sums[i] = row_sum(i, m, pa);
        bubble_sort(n, row_sums, pa, m);
        print_mat(n, m, pa);
    }
    print_error(ec);
    return ec;
}

void transform(size_t n, size_t m, int *mat, int **pa)
{
    for (size_t i = 0; i < n; i++)
        pa[i] = mat + m * i;
}

int validate_dim(size_t dim)
{
    return (dim > 0) && (dim <= N);
}

int input_mat(size_t *n, size_t *m, int **pa)
{
    if (scanf("%zu %zu", n, m) != 2)
        return input_error;
    if (!validate_dim(*n) || !validate_dim(*m))
        return input_error;

    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *m; j++)
            if (scanf("%d", &pa[i][j]) != 1)
                return input_error;
    return ok;
}

void print_mat(size_t n, size_t m, int **pa)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", pa[i][j]);
        printf("\n");
    }
}

void print_error(const int ec)
{
    switch (ec)
    {
        case ok:
            break;
        case input_error:
            printf("Input error\n");
            break;
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_rows(size_t m, int *row1, int *row2)
{
    for (size_t j = 0; j < m; j++)
        swap(&row1[j], &row2[j]);
}

void bubble_sort(size_t len, int *values, int **pa, size_t m)
{
    size_t i, j;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - i - 1; j++)
            if (values[j] > values[j + 1])
            {
                swap(&values[j], &values[j + 1]);
                swap_rows(m, pa[j], pa[j + 1]);
            }
}

int row_sum(size_t row, size_t m, int **pa)
{
    int res = 0;
    for (size_t i = 0; i < m; i++)
    {
        res += pa[row][i];
    }
    return res;
}
