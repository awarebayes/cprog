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
    input_error
};

int cin_arr(int *arr, int *len);
int find_even_sum(int *arr, int len);

int main()
{
    int arr[N];
    int len = 0;
    int ec = cin_arr(arr, &len);
    if (ec)
        printf("Array overflow\n");
    else
    {
        int sum = find_even_sum(arr, len);
        printf("%d\n", sum);
    }
    return ec;
}

int cin_arr(int *arr, int *len)
{
    int ec = ok;
    scanf("%d", len);
    if (*len > N || *len < 0)
        ec = input_error;
    else
    {
        for (int i = 0; i < *len; i++)
            scanf("%d", arr + i);
    }
    return ec;
}

int find_even_sum(int *arr, int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
        sum += (arr[i] % 2) ? 0 : arr[i];
    return sum;
}