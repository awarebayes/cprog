/*
 * Задача 1 лабы 3
 * Написал: Щербина Михаил
 * 2.1
 * Задача №1
 * По матрице получить и вывести на экран одномерный массив, присвоив его 𝑘-тому
 * элементу значение 1, если выполняется указанное условие, и значение 0 в иных случаях:
 * 0. элементы 𝑘-го столбца упорядочены по убыванию; 
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

int main()
{
    int mat[N][N];
    int res[N];
    size_t m, n;
    int ec = ok;
    ec = input_mat(&n, &m, mat);
    if (!ec)
    {
        apply_cols(n, m, mat, res);
        print_arr(m, res);
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

int elements_descending(size_t n, size_t idx, int (*mat)[N])
{
    int flag = 1;
    for (size_t i = 0; i < (n-1) && flag; i++)
        if (mat[i][idx] > mat[i+1][idx])
            flag = 0;
    return flag;
}

void apply_cols(size_t n, size_t m, int (*mat)[N], int *out)
{
    for (size_t i=0; i<m; i++)
        out[i] = elements_descending(n, i, mat);
}