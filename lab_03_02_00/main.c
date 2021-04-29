/*
 * Задача 2 лабы 3
 * Написал: Щербина Михаил
 * Вставить строку из чисел 100 после каждой строки, в которой количество элементов,
 * начинающихся на заданную цифру, равно количеству элементов, заканчивающихся
 * на эту же цифру. В ситуации, когда таких чисел не обнаружено вообще, строку из
 * сотен не вставлять. Цифра вводится в виде числа после ввода матрицы.
 */

#include <stdio.h>

#define N 20
#define M 20

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
int starts_with(int n, size_t digit);
int ends_with(int n, size_t digit);
int gen_append_after(size_t n, size_t m, int **pa, int *append_after, size_t digit);
int input_digit(size_t *digit);
void transform(size_t n, size_t m, int *mat, int **ptr);
void rshift_row(size_t n, size_t m, size_t from, int **pa);
void insert_hundreds(int n_appended, size_t n, size_t m, int *append_after, int **pa);

int main()
{
    int mat[N][N];
    int *pa[N * 2];
    int append_after[N];
    size_t m, n;
    size_t digit;
    int ec = ok;

    transform(N, M, *mat, pa);
    ec = input_mat(&n, &m, pa);
    if (!ec)
        ec = input_digit(&digit);
    if (!ec)
    {
        int n_appended = gen_append_after(n, m, pa, append_after, digit);
        insert_hundreds(n_appended, n, m, append_after, pa);
        print_mat(n + n_appended, m, pa);
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

int input_digit(size_t *digit)
{
    if (scanf("%zu", digit) != 1)
        return input_error;
    if (*digit >= 10)
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
        if (pa[i][idx] > pa[i + 1][idx])
            flag = 0;
    return flag;
}

void apply_cols(size_t n, size_t m, int **pa, int *out)
{
    for (size_t i = 0; i < m; i++)
        out[i] = elements_descending(n, i, pa);
}

int starts_with(int n, size_t digit)
{
    if (n < 0)
        n *= -1;
    while (n >= 10)
        n /= 10;
    return (n % 10) == (int)digit;
}

int ends_with(int n, size_t digit)
{    
    if (n < 0)
        n *= -1;
    return (n % 10) == (int)digit;
}

int gen_append_after(size_t n, size_t m, int **pa, int *append_after, size_t digit)
{
    int current = 0;
    for (size_t i = 0; i < n; i++)
    {
        size_t n_start = 0;
        size_t n_end = 0;
        for (size_t j = 0; j < m; j++)
        {
            n_start += starts_with(pa[i][j], digit);
            n_end += ends_with(pa[i][j], digit);
        }
        if (n_start == n_end && n_start != 0)
        {
            append_after[current] = i;
            current++;
        }
    }
    return current;
}

void rshift_row(size_t n, size_t m, size_t from, int **pa)
{
    for (size_t i = n; i > from; i--)
        for (size_t j = 0; j < m; j++)
            pa[i][j] = pa[i - 1][j];
}

void insert_hundreds(int n_appended, size_t n, size_t m, int *append_after, int **pa)
{
    int shifted = 0;
    for (int i = 0; i < n_appended; i++)
    {
        rshift_row(n + n_appended, m, append_after[i] + shifted, pa);
        shifted++;
        for (size_t j = 0; j < m; j++)
            pa[append_after[i] + shifted][j] = 100;
    }
}