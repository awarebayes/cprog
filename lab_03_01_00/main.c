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
void apply_cols(size_t n, size_t m, int **pa, int *out);
void print_arr(size_t n, int *arr);
void transform(size_t n, size_t m, int *mat, int **ptr);

int main()
{
    int mat[N][N];
    int *pa[N];
    int res[N];
    size_t m, n;
    int ec = ok;
    transform(N, M, *mat, pa);
    ec = input_mat(&n, &m, pa);
    if (n == 1 && !ec)
    {
        for (size_t i = 0; i < m; i++)
            printf("%d ", 0);
        printf("\n");
    } 
    else if (!ec)
    {
        apply_cols(n, m, pa, res);
        print_arr(m, res);
    }
    print_error(ec);
    return ec;
}

void transform(size_t n, size_t m, int *mat, int **ptr)
{
    for (size_t i = 0; i < n; i++)
        ptr[i] = mat + i * m;
}

int validate_dim(size_t dim)
{
    return (dim > 0) && (dim <= N);
}

int input_mat(size_t *n, size_t *m, int **pa)
{
    int ec = ok;
    if (scanf("%zu %zu", n, m) != 2)
        ec = input_error;
    if (ec || !validate_dim(*n) || !validate_dim(*m))
        ec = input_error;

    for (size_t i = 0; i < *n && !ec; i++)
        for (size_t j = 0; j < *m && !ec; j++)
            if (scanf("%d", &pa[i][j]) != 1)
                ec = input_error;
    return ec;
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

int elements_descending(size_t n, size_t idx, int **pa)
{
    int flag = 1;
    for (size_t i = 0; i < (n - 1) && flag; i++)
        if (pa[i + 1][idx] >= pa[i][idx])
            flag = 0;
    return flag;
}

void apply_cols(size_t n, size_t m, int **pa, int *out)
{
    for (size_t i = 0; i < m; i++)
        out[i] = elements_descending(n, i, pa);
}