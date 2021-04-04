/*
 * Задача 2 лабы 3
 * Написал: Щербина Михаил
 * Вставить строку из чисел 100 после каждой строки, в которой количество элементов,
 * начинающихся на заданную цифру, равно количеству элементов, заканчивающихся
 * на эту же цифру. В ситуации, когда таких чисел не обнаружено вообще, строку из
 * сотен не вставлять. Цифра вводится в виде числа после ввода матрицы.
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
int starts_with(int n, size_t digit);
int ends_with(int n, size_t digit);
int gen_append_after(size_t n, size_t m, int (*mat)[N], int(*append_after), size_t digit);
void append_after_mat(size_t m, size_t n, size_t n_appended, int (*mat)[N],
                      int (*extended_mat)[N], int append_after[N]);
int input_digit(size_t *digit);

int main()
{
    int mat[N][N];
    int extended_mat[2 * N][N];
    int append_after[N] = {1, 2};
    size_t m = 4, n = 4;
    size_t digit = 1;
    int ec = ok;
    ec = input_mat(&n, &m, mat);
    ec = input_digit(&digit);
    printf("\n");
    if (!ec)
    {
        int n_appended = gen_append_after(n, m, mat, append_after, digit);
        append_after_mat(m, n, n_appended, mat, extended_mat, append_after);
        print_mat(n + n_appended, m, extended_mat);
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

int input_digit(size_t *digit)
{
    if (scanf("%zu", digit) != 1)
        return input_error;
    if (*digit > 10)
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
    for (size_t i = 0; i < (n - 1) && flag; i++)
        if (mat[i][idx] > mat[i + 1][idx])
            flag = 0;
    return flag;
}

void apply_cols(size_t n, size_t m, int (*mat)[N], int *out)
{
    for (size_t i = 0; i < m; i++)
        out[i] = elements_descending(n, i, mat);
}

int starts_with(int n, size_t digit)
{
    while (n > 10)
        n /= 10;
    return (n % 10) == (int)digit;
}

int ends_with(int n, size_t digit)
{
    return (n % 10) == (int)digit;
}

int gen_append_after(size_t n, size_t m, int (*mat)[N], int(*append_after), size_t digit)
{
    int current = 0;
    for (size_t i = 0; i < n; i++)
    {
        size_t n_start = 0;
        size_t n_end = 0;
        for (size_t j = 0; j < m; j++)
        {
            n_start += starts_with(mat[i][j], digit);
            n_end += ends_with(mat[i][j], digit);
        }
        if (n_start == n_end && n_start != 0)
        {
            append_after[current] = i;
            current++;
        }
    }
    return current;
}

void append_after_mat(size_t m, size_t n, size_t n_appended, int (*mat)[N],
                      int (*extended_mat)[N], int append_after[N])
{
    size_t next_append = 0;
    size_t mat_idx = 0;
    for (size_t i = 0; i < n + n_appended; i++)
    {
        if (append_after[next_append] < (int)mat_idx && next_append < n_appended)
        {
            // append
            for (size_t j = 0; j < m; j++)
                extended_mat[i][j] = 100;
            next_append++;
        }
        else
        {
            // copy
            for (size_t j = 0; j < m; j++)
                extended_mat[i][j] = mat[mat_idx][j];
            mat_idx++;
        }
    }
}