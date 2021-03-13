
/*
 * Написал Щербина Михаил ИУ7-25Б
 * Задача 2 
 * Сформировать и вывести на экран новый массив, в который скопировать элементы
 * исходного массива, которые больше среднего арифметического его элементов.
 * gcc -std=c99 -Werror -Wall -Wfloat-equal -Wfloat-conversion \
   -lm ./lab_02_02_00/main.c -o ./bin/lab2 && ./bin/lab2
 */

#include <stdio.h>
#define N 10

enum error_code 
{ 
    ok,
    input_error
};

int cin_arr(int *arr, int *len);
void print_arr(int *arr, int len);
void print_error(int ec);
void arr_copy_more_than(int *from, int *to, int from_len, int *to_len, float cmp);
float find_mean(int *arr, int len);

int main()
{
    int arr_len = 0;
    int arr[N];

    int ec = cin_arr(arr, &arr_len);
    if (!ec)
    {
        float mean = find_mean(arr, arr_len); 

        int arr_copy[N];
        int arr_copy_len = 0;

        arr_copy_more_than(arr, arr_copy, arr_len, &arr_copy_len, mean);
        print_arr(arr_copy, arr_copy_len);
    }
    print_error(ec);
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

void print_arr(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void print_error(int ec)
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

float find_mean(int *arr, int len)
{
    float sum = 0;
    for (int i = 0; i < len; i++)
        sum += arr[i];
    return sum / len;
}

void arr_copy_more_than(int *from, int *to, int from_len, int *to_len, float cmp)
{
    int to_cur = 0; // current to index
    for (int i = 0; i < from_len; i++)
    {
        if (from[i] > cmp)
        {
            to[to_cur] = from[i];
            to_cur += 1;
        }
    }
    *to_len = to_cur;
}

