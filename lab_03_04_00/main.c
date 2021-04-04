/*
 * 2.3
 * Упорядочить строки матрицы:
 * 0. по возрастанию суммы их элементов;
 * Задача 4 лабы 3
 * 0. Найти и вывести на экран минимальное нечётное
 * число, расположенное под главной диагональю. 
 * Написал: Щербина Михаил
 */

#include <stdio.h>
#include <limits.h>

#define N 10

enum error_code
{
    ok,
    input_error,
};

int validate_dim(size_t dim);
int input_mat(size_t *n, int (*mat)[N]);
void print_mat(size_t n, size_t m, int (*mat)[N]);
void print_error(int ec);
void print_arr(size_t n, int *arr);


int main()
{
    int mat[N][N];
    size_t n;
    int min = INT_MAX;

    int ec = ok;
    ec = input_mat(&n, mat);
    if (!ec)
    {
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++)
                if (i > j && mat[i][j] < min && mat[i][j] % 2)
                    min = mat[i][j];
        printf("%d\n", min);
    }
    print_error(ec);
    return ec;
}

int validate_dim(size_t dim)
{
    return (dim > 1) && (dim <= N);
}

int input_mat(size_t *n, int (*mat)[N])
{

    // printf("Input n and m:\n");
    if (scanf("%zu", n) != 1)
        return input_error;
    if (!validate_dim(*n))
        return input_error;

    // printf("Start inputting matrix\n");
    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *n; j++)
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