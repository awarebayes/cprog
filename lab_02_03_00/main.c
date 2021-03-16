
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
    input_error,
    empty_arr
};

int cin_arr(int *arr, size_t *len);
void print_arr(int *arr, size_t len);
void print_error(int ec);
void arr_filter_palindrome(int *arr, size_t len, size_t *new_len);
int is_palindrome(int num);

int main()
{
    size_t arr_len = 0;
    int arr[N];

    int ec = cin_arr(arr, &arr_len);
    if (!ec)
    {
        size_t new_len;
        arr_filter_palindrome(arr, arr_len, &new_len);
        ec = (new_len != 0) ? ok : empty_arr;
        if (!ec)
            print_arr(arr, new_len);
    }

    print_error(ec);
    return ec;
}

int cin_arr(int *arr, size_t *len)
{
    int ec = ok;
    scanf("%zu", len);
    if (*len > N)
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
    case empty_arr:
        printf("New array is empty\n");
        break;
    }
}

int nth_left_digit(int num, size_t pos)
{
    for (size_t i = 0; i < pos; i++)
        num /= 10;
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
    if (num < 0)
        return 0;

    size_t n_d = n_digits(num);
    if (n_d == 1)
        return 1;
    
    int res = 1;
    for (size_t i = 0; i < n_d; i++)
    {
        int d_1 = nth_left_digit(num, i);
        int d_2 = nth_left_digit(num, n_d - i - 1);
        if (d_1 != d_2)
            res = 0;
        if (!res)
            break;
    }
    return res;
}

void arr_filter_palindrome(int *arr, size_t len, size_t *new_len)
{
    int cur = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (!is_palindrome(arr[i]))
        {
            arr[cur] = arr[i];
            cur += 1;
        }
    }
    *new_len = cur;
}