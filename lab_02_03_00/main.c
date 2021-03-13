
/*
 * Написал Щербина Михаил ИУ7-25Б
 * Задача 2 
 * 0. Удалить из исходного массива все элементы,
 *  которые являются числами-палиндромами.
 * gcc -std=c99 -Werror -Wall -Wfloat-equal -Wfloat-conversion \
   -lm ./lab_02_03_00/main.c -o ./bin/lab3 && ./bin/lab3
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
void arr_filter_palindrome(int *arr, int len, int *new_len);

int main()
{
    int arr_len = 0;
    int arr[N];

    int ec = cin_arr(arr, &arr_len);
    if (!ec)
    {
        int new_len;
        arr_filter_palindrome(arr, arr_len, &new_len);
        print_arr(arr, new_len);
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

int nth_right_digit(int num, int pos)
{
    if (pos < 0)
    {
        printf("Something went wrong, got pos %d\n", pos);
        return 0;
    }
    for (int i = 0; i < pos; i++)
        num %= 10;
    return num % 10;
}

int n_digits(int num)
{
    int n = 0;
    while (num > 0)
    {
        num /= 10;
        n += 1;
    }
    return n;
}

int is_palindrome(int num)
{
    int n_d = n_digits(num);
    int res = 1;
    for (int i = 0; i < n_d; i++)
    {
        if (nth_right_digit(num, i) != nth_right_digit(num, n_d - i))
            res = 0;
        if (!res)
            break;
    }
    return res;
}

void arr_filter_palindrome(int *arr, int len, int *new_len)
{
    int cur = 0;
    for (int i = 0; i < len; i++)
    {
        if (!is_palindrome(arr[i]))
        {
            arr[cur] = arr[i];
            cur += 1;
        }
    }
    *new_len = cur;
}