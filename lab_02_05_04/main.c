/*
 * Написал Щербина Михаил ИУ7-25Б
 * Задача 5 
 * При решении пятой задачи в методических целях запрещено использовать выражения
 * вида a[i] и вообще квадратные скобки. Вместо указанного выражения используется
 * выражение *pa, где pa — указатель на элемент массива с индексом 𝑖 (именно на i-ый элемент,
 * а не выражение вида *(pa + i)). Также нельзя передавать как аргумент размер массива
 * в элементах.
 * Вместо этого предлагается использовать пару указателей: на первый (нулевой)
 * элемент массива и на элемент массива, расположенный за последним. Ситуация, когда эти
 * указатели совпадают, означает пустоту обрабатываемого массива.
 * 
 * 4. Найти и вывести на экран количество уникальных чисел в массиве.
 * 
 * gcc -std=c99 -Werror -Wall -Wfloat-equal -Wfloat-conversion \
   -lm ./lab_02_05_00/main.c -o ./bin/lab5 && ./bin/lab5
 */

#include <stdio.h>
#define N 10

enum error_code
{
    ok,
    input_error,
};

int cin_arr(int *begin, int **end);
void print_arr(const int *begin, const int *end);
void print_error(int ec);
int n_unique(const int *begin, const int *end);

int main()
{
    int arr[N];

    int *begin = arr;
    int *end = NULL;

    int ec = cin_arr(begin, &end);
    if (!ec)
    {
        printf("%d\n", n_unique(begin, end));
    }

    print_error(ec);
    return ec;
}

int cin_arr(int *begin, int **end)
{
    int ec = ok;
    size_t len = 0;
    if (scanf("%zu", &len) != 1 || len > N || len == 0)
        ec = input_error;
    else
    {

        *end = begin + len;
        for (int *i = begin; i < *end; i++)
            if (scanf("%d", i) != 1)
            {
                ec = input_error;
                break;
            }
    }
    return ec;
}

void print_arr(const int *begin, const int *end)
{
    for (const int *i = begin; i < end; i++)
        printf("%d ", *i);
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

int n_unique(const int *begin, const int *end)
{
    int count = 0;
    for (const int *i = begin; i < end; i++)
    {
        int is_unique = 1;
        for (const int *j = begin; j < i; j++)
        {
            if (*j == *i)
            {
                is_unique = 0;
                break;
            }
        }
        if (is_unique)
            count += 1;
    }
    return count;
}