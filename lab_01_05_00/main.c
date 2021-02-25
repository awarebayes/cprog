/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 5 лабораторной 1.
 * С клавиатуры вводятся целое 𝑎 и целое неотрицательное 𝑛. Вычислить и вывести на
 * экран 𝑎^𝑛 приняв, что любое число в нулевой степени равно единице.
 * gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal  -Wfloat-conversion -lm ./lab_01_05_00/main.c -o ./bin/lab5 && ./bin/lab5
 */

#include <stdio.h>

int powi(int a, int n);

int main(void)
{
    int a; ///< number
    int n; ///< power

    printf("Enter two numbers: \n");

    if (scanf("%d %d", &a, &n) != 2)
    {
        printf("Input Error\n");
        return 1;
    }

    // sanity check
    if (n <= 0)
    {
        printf("Power should be non negative\n");
        return 1;
    }

    // final result
    int res = powi(a, n);
    printf("%d\n", res); 
    return 0;
}

/*
 * a^n for integers
 */
int powi(int a, int n)
{
    long res = 1;
    while (n > 0)
    {
        res *= a;
        n--;
    }
    return res;
}

