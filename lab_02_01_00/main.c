/*
 * Написал Щербина Михаил ИУ7-25Б
 * Задача 1
 * 0. Найти и вывести на экран сумму чётных элементов массива.
 * gcc -std=c99 -Werror -Wall -Wfloat-equal -Wfloat-conversion \
   -lm ./lab_02_01_00/main.c -o ./bin/lab1 && ./bin/lab1
 */

#include <stdio.h>

#define N 10

enum error_code
{
    ok,
    input_error,
    no_even
};

int cin_arr(int *arr, size_t *len);
int find_even_sum(const int *arr, const size_t len, int *has_even);
void print_error(const int ec);

int main()
{
    int arr[N];
    size_t len = 0;
    int has_even = 0;
    int ec = cin_arr(arr, &len);
    if (ec)
        printf("Input error\n");
    else
    {
        int sum = find_even_sum(arr, len, &has_even);
        if (!has_even)
            ec = no_even;
        else
            printf("%d\n", sum);
    }
    print_error(ec);
    return ec;
}

int cin_arr(int *arr, size_t *len)
{
    int ec = ok;
    if (scanf("%zu", len) != 1 || *len > N || *len == 0)
        ec = input_error;
    else
    {
        for (size_t i = 0; i < *len; i++)
            if (scanf("%d", arr + i) != 1)
            {
                ec = input_error;
                break;
            }
    }
    return ec;
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
        case no_even:
            printf("No even\n");
            break;
    }
}


int find_even_sum(const int *arr, const size_t len, int *has_even)
{
    int sum = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (arr[i] % 2 == 0)
        { 
            sum += arr[i];
            *has_even = 1;
        }
    }
    return sum;
}