/* 
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 5
 * Элементы матрицы, которые являются простыми числами, в порядке обхода мат-
 * рицы по строкам поместить в одномерный массив, развернуть массив, и вернуть
 * элементы из массива в матрицу в том же порядке, в котором они помещались в
 * массив. Если в матрице нет простых чисел, считать ситуацию ошибочной.
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
int input_mat(size_t *n, size_t *m, int **pa);
void print_mat(size_t n, size_t m, int **pa);
void print_error(const int ec);
int is_prime(int num);
size_t find_primes(size_t n, size_t m, int **pa, int *primes, int *has_primes);
void reverse_arr(size_t n, int *arr);
void replace_primes(size_t n, size_t m, int **pa, int *with);

int main()
{
    int mat[N][M];
    int *pa[N];
    transform(N, M, *mat, pa);
    int primes[N*M];
    size_t n, m;
    int has_primes = 0;
    int ec = ok;
    ec = input_mat(&n, &m, pa);
    if (!ec)
    {
        size_t n_found = find_primes(n, m, pa, primes, &has_primes);
        if (!has_primes)
            ec = no_primes;
        else
        {
            reverse_arr(n_found, primes);
            replace_primes(n, m, pa, primes);
            print_mat(n, m, pa);
        }
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
        case no_primes:
            printf("No primes\n");
            break;
    }
}

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    int flag = 1;
    for (int i = 2; i <= sqrt(num) && flag; i++)
    {
        if (num % i == 0)
            flag = 0;
    }
    return flag;
}

size_t find_primes(size_t n, size_t m, int **pa, int *primes, int *has_primes)
{
    size_t n_found = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (is_prime(pa[i][j]))
            {
                primes[n_found++] = pa[i][j];
                *has_primes = 1;
            }
        }
    }
    return n_found;
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void reverse_arr(size_t n, int *arr)
{
    for (size_t i = 0; i < (n / 2); i++)
    {
        swap(&arr[i], &arr[n - i - 1]);
    }
}

void replace_primes(size_t n, size_t m, int **pa, int *with)
{
    int k = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_prime(pa[i][j]))
            {
                pa[i][j] = with[k];
                k++;
            }
}