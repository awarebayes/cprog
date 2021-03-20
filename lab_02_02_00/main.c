
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
    input_error,
    empty_arr,
    equal_arr,
};

int cin_arr(int *arr, size_t *len);
void print_arr(int *arr, size_t len);
void print_error(int ec);
size_t arr_copy_more_than(int *from, int *to, size_t from_len, float cmp);
float find_mean(int *arr, size_t len);

int main()
{
    size_t arr_len = 0;
    int arr[N];

    int ec = cin_arr(arr, &arr_len);
    if (!ec)
    {
        float mean = find_mean(arr, arr_len);

        int arr_copy[N];
        size_t arr_copy_len = 0;

        arr_copy_len = arr_copy_more_than(arr, arr_copy, arr_len, mean);
        ec = (arr_copy_len != 0) ? ok : equal_arr;
        if (!ec)
            print_arr(arr_copy, arr_copy_len);
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

void print_arr(int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
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
        case equal_arr:
            printf("Array of equals\n");
            break;
    }
}

float find_mean(int *arr, size_t len)
{
    float sum = 0;
    for (size_t i = 0; i < len; i++)
        sum += arr[i];
    return sum / len;
}

size_t arr_copy_more_than(int *from, int *to, size_t from_len, float cmp)
{
    int to_cur = 0; // current to index
    for (size_t i = 0; i < from_len; i++)
    {
        if (from[i] > cmp)
        {
            to[to_cur] = from[i];
            to_cur += 1;
        }
    }
    return to_cur;
}
