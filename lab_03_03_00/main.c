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
void apply_cols(size_t n, size_t m, int (*mat)[N], int *out);
void print_arr(size_t n, int *arr);
void bubble_sort_index(size_t len, int *values, size_t (*index)[N]);
int row_sum(size_t row, size_t m, int (*mat)[N]);
void reorder_by_indices(size_t n, size_t m, int (*mat)[N], size_t *row_indices);
void swap_rows(size_t n, int (*a)[N], int (*b)[N]);

int main()
{
    int mat[N][N] = {
        {61, 21, 52, 50},
        {74, 89, 45, 35},
        {89, 79, 60, 25},
        {22, 36, 30, 54},
    };
    size_t m = 4, n = 4;

    int row_sums[N];
    size_t row_indices[N];

    int ec = ok;
    // ec = input_mat(&n, &m, mat);
    if (!ec)
    {
        for (size_t i = 0; i < n; i++)
        {
            row_sums[i] = row_sum(i, m, mat);
            row_indices[i] = i;
        }
        bubble_sort_index(n, row_sums, &row_indices);
        reorder_by_indices(n, m, mat, row_indices);
        print_mat(n, m, mat);
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

void swap_size_t(size_t *a, size_t *b)
{
    size_t temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_rows(size_t n, int (*a)[N], int (*b)[N])
{
    int buf[N];
    for (size_t i = 0; i < n; i++)
    {
        buf[i] = (*a)[i];
        (*a)[i] = (*b)[i];
    }
    for (size_t i = 0; i < n; i++)
        (*b)[i] = buf[i];
}

void bubble_sort_index(size_t len, int *values, size_t (*index)[N])
{
    size_t i, j;
    int tmp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - i - 1; j++)
            if (values[j] > values[j + 1])
            {
                swap(&values[j], &values[j + 1]);
                tmp = (*index)[j];
                (*index)[j] = (*index)[j + 1];
                (*index)[j + 1] = tmp;
            }
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

void reorder_by_indices(size_t n, size_t m, int (*mat)[N], size_t *row_indices)
{
    for (size_t i = 0; i < n; i++)
    {
        size_t idx = row_indices[i];
        while (i != idx)
        {
            swap_rows(m, &mat[i], &mat[idx]);
            swap_size_t(&row_indices[i], &row_indices[idx]);
            idx = row_indices[i];
        }
    }
}