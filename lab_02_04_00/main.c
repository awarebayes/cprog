/*
 * Написал Щербина Михаил ИУ7-25Б
 * Задача 4 
 * В четвёртой задаче необходимо организовать ввод массива по концевому признаку. В
 * качестве концевого признака выступает любая ошибка, которая возникает при очередном
 * вводе значения с помощью функции scanf. Например, при вводе последовательности
 * 1 2 3 a
 * должен быть сформирован массив из трёх элементов со значениями
 * 𝐴[0] = 1, 𝐴[1] = 2, 𝐴[2] = 3.
 * В случае, если массив уже заполнен, а концевой признак ещё не наступил,
 * ввод элементов в массив прекращается. Такое «переполнение» не считается ошибкой: программа
 * должна обработать полученный массив из 10 элементов,
 * но функция main в такой ситуации должна вернуть специальный код ошибки, равный 100.
 * Варианты
 * 
 * 0. Упорядочить массив по возрастанию с помощью сортировки пузырьком (англ. Bubble
 * Sort) и вывести на экран
 * gcc -std=c99 -Werror -Wall -Wfloat-equal -Wfloat-conversion \
   -lm ./lab_02_04_00/main.c -o ./bin/lab4 && ./bin/lab4
 */


#include <stdio.h>
#define N 10

enum error_code
{
    ok,
    input_error,
    arr_overflow = 100
};

int cin_arr_ring(int *arr, int *ec);
void print_arr(const int *arr, const size_t len);
void print_error(const int ec);
void bubble_sort(int *arr, size_t len);

int main()
{
    int arr[N];
    int ec = ok;

    int len = cin_arr_ring(arr, &ec);
    if (!ec || ec == arr_overflow)
    {
        bubble_sort(arr, len);
        print_arr(arr, len);
    }
    print_error(ec);
    return ec;
}

int cin_arr_ring(int *arr, int *ec)
{
    size_t len = 0;
    int temp;
    int flag = 1;
    while (flag)
    {
        if (scanf("%d", &temp) == 1)
        {
            if (len < N)
                arr[len] = temp;
        }
        else    
            flag = 0;
        len++;
    }
    if (len == 0)
        *ec = input_error;
    else if (len > N)
    {
        *ec = arr_overflow;
        len = N;
    }
    return len;
}

void print_arr(const int *arr, const size_t len)
{
    for (size_t i = 0; i < len; i++)
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
        case arr_overflow:
            break;
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
        for (size_t j = i; j < len; j++)
            if (arr[j] < arr[i])
                swap(&arr[j], &arr[i]);
}