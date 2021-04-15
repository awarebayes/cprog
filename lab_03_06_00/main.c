/* 
 * Написал Щербина Михаил ИУ7-15Б.
 * 
 * Задача 5
 * 0. Приняв с клавиатуры число строк и столбцов матрицы, заполнить прямоугольную
 *    целочисленную матрицу «ходом быка» с начала: нечётные столбцы проходить сверху
 */

#include <stdio.h>
#include <math.h>

#define N 10
#define M 10

enum error_code
{
    ok,
    input_error,
    no_primes
};

void transform(size_t n, size_t m, int *mat, int **ptr);
int input_dim(size_t *n, size_t *m);
void print_mat(size_t n, size_t m, int **pa);
void print_error(const int ec);
int is_prime(int num);
size_t find_primes(size_t n, size_t m, int **pa, int *primes, int *has_primes);
void reverse_arr(size_t n, int *arr);
void replace_primes(size_t n, size_t m, int **pa, int *with);
void fill_bull(size_t n, size_t m, int **pa);

int main()
{
    int mat[N][M];
    int *pa[N];
    transform(N, M, *mat, pa);
    size_t n, m;
    int ec = ok;
    ec = input_dim(&n, &m);
    if (!ec)
    {
        fill_bull(n, m, pa);
        print_mat(n, m, pa);
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
    return (dim >= 1) && (dim <= N);
}

int input_dim(size_t *n, size_t *m)
{
    // printf("Input n and m:\n");
    if (scanf("%zu %zu", n, m) != 2)
        return input_error;
    if (!validate_dim(*n) || !validate_dim(*m))
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
    case no_primes:
        printf("No primes\n");
        break;
    }
}

void fill_bull(size_t n, size_t m, int **pa)
{
    int k = 0;
    int idx = 0;
    int counter = 1;
    for (size_t j = 0; j < m; j++)
    {
        for (size_t i = 0; i < n; i++)
        {
            idx = (k % 2 == 0) ? i : n - i - 1;
            pa[idx][j] = counter;
            counter++;
        }
        k++;
    }
}