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
    zero_sum
};

int cin_arr(int *arr, size_t *len);
int find_even_sum(int *arr, size_t len);

int main()
{
    int arr[N];
    size_t len = 0;
    int ec = cin_arr(arr, &len);
    if (ec)
        printf("Input error\n");
    else
    {
        int sum = find_even_sum(arr, len);
        if (sum == 0)
            ec = zero_sum;
        else
            printf("%d\n", sum);
    }
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

int find_even_sum(int *arr, size_t len)
{
    int sum = 0;
    for (size_t i = 0; i < len; i++)
        sum += (arr[i] % 2) ? 0 : arr[i];
    return sum;
}