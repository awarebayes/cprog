/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 5 лабораторной 1.
 * С клавиатуры вводятся целое 𝑎 и целое неотрицательное 𝑛. Вычислить и вывести на
 * экран 𝑎^𝑛 приняв, что любое число в нулевой степени равно единице.
 * gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal  -Wfloat-conversion -lm ./lab_01_05_00/main.c -o ./bin/lab5 && ./bin/lab5
 */

#include <stdio.h>

int powi(int a, int n);
void print_error(int error_flag);

int main(void)
{
    int a; ///< number
    int n; ///< power
    int error_flag = 0;

    printf("Enter two numbers: \n");

    if (scanf("%d %d", &a, &n) != 2)
        error_flag = 1;
    // sanity check
    else if (n <= 0)
        error_flag = 2;
    else
    {
        // final result
        int res = powi(a, n);
        printf("%d\n", res); 
    }
    print_error(error_flag);
    return error_flag;
}

/*
 * a^n for integers
 */
int powi(int a, int n)
{
    int res = 1;
    while (n > 0)
    {
        res *= a;
        n--;
    }
    return res;
}

void print_error(int error_flag)
{
    switch (error_flag)
    {
        case 1:
            printf("Input Error\n");
            break;
        case 2:
            printf("N should be positive\n");
            break;
        default:
            break;
    }
}
