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
#define M 10

enum error_code
{
    ok,
    input_error,
    no_min
};

int validate_dim(size_t dim);
int input_mat(size_t *n, int **pa);
void print_mat(size_t n, size_t m, int **pa);
void print_error(int ec);
int find_min(size_t n, int **pa, int *has_min);
void transform(size_t n, size_t m, int *mat, int **ptr);

int main()
{
    int mat[N][N];
    int *pa[N];
    transform(N, M, *mat, pa);
    size_t n;
    int ec = ok;

    ec = input_mat(&n, pa);
    int has_min = 0;

    if (!ec)
    {
        int min = find_min(n, pa, &has_min);
        if (has_min)
            printf("%d\n", min);
        else
            ec = no_min;
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
    return (dim > 1) && (dim <= N);
}

int input_mat(size_t *n, int **pa)
{
    // printf("Input n and m:\n");
    if (scanf("%zu", n) != 1)
        return input_error;
    if (!validate_dim(*n))
        return input_error;

    // printf("Start inputting matrix\n");
    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *n; j++)
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
        case no_min:
            printf("No min\n");
            break;
    }
}

int find_min(size_t n, int **pa, int *has_min)
{
    int min = INT_MAX;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            if (i > j && pa[i][j] < min && pa[i][j] % 2)
            {
                min = pa[i][j];
                *has_min = 1;
            }
    return min;
}