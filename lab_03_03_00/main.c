/*
 * 2.3
 * Упорядочить строки матрицы:
 * 0. по возрастанию суммы их элементов;
 * Задача 2 лабы 3
 * Написал: Щербина Михаил
 */

#include <stdio.h>

#define N 10

enum error_code
{
    ok,
    input_error,
};

int validate_dim(size_t dim);
int input_mat(size_t *n, size_t *m, int (*mat)[N]);
void print_mat(size_t n, size_t m, int (*mat)[N]);
void print_error(int ec);
void print_arr(size_t n, int *arr);
void bubble_sort(size_t len, int values[N]);
int row_sum(size_t row, size_t m, int (*mat)[N]);
void copy_rows(size_t n, int (*from)[N], int (*to)[N]);
void reorder(size_t n, size_t m, int (*mat)[N], int *row_sums, int (*sorted_mat)[N]);

int main()
{
    int mat[N][N];
    int sorted_mat[N][N];
    size_t m, n;

    int row_sums[N] = {0};

    int ec = ok;
    ec = input_mat(&n, &m, mat);
    if (!ec)
    {
        for (size_t i = 0; i < n; i++)
            row_sums[i] = row_sum(i, m, mat);
        bubble_sort(n, row_sums);
        reorder(n, m, mat, row_sums, sorted_mat);
        print_mat(n, m, sorted_mat);
    }
    print_error(ec);
    return ec;
}

int validate_dim(size_t dim)
{
    return (dim > 0) && (dim <= N);
}

int input_mat(size_t *n, size_t *m, int (*mat)[N])
{

    // printf("Input n and m:\n");
    if (scanf("%zu %zu", n, m) != 2)
        return input_error;
    if (!validate_dim(*n) || !validate_dim(*m))
        return input_error;

    // printf("Start inputting matrix\n");
    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *m; j++)
            if (scanf("%d", &mat[i][j]) != 1)
                return input_error;
    return ok;
}

void print_mat(size_t n, size_t m, int (*mat)[N])
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void print_arr(size_t n, int *arr)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
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

void copy_rows(size_t n, int (*from)[N], int (*to)[N])
{
    for (size_t i = 0; i < n; i++)
    {
        (*to)[i] = (*from)[i];
    }
}

void bubble_sort(size_t len, int values[N])
{
    size_t i, j;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - i - 1; j++)
            if (values[j] > values[j + 1])
                swap(&values[j], &values[j + 1]);
}

int row_sum(size_t row, size_t m, int (*mat)[N])
{
    int res = 0;
    for (size_t i = 0; i < m; i++)
    {
        res += mat[row][i];
    }
    return res;
}

void reorder(size_t n, size_t m, int (*mat)[N], int *row_sums, int (*sorted_mat)[N])
{
    size_t last = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (row_sums[last] == row_sum(j, m, mat) && last < n)
            {
                copy_rows(m, &mat[j], &sorted_mat[last]);
                last++;
            }
        }
    }
}