/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 7 лабораторной 1.
 * Приняв с клавиатуры 𝑥 и 𝜀, вычислить и вывести на экран вычисленное с точностью E
 * приближённое значение 𝑠(𝑥) и точное значение 𝑓(𝑥) функции 𝑓,
 * абсолютную ∆ и относительную 𝛿 погрешности:
 * Мой вариант: exp(x)
 * gcc -std=c99 -Werror -Wall  -lm ./lab_01_07_24/main.c -o ./bin/lab7 && ./bin/lab7
 */

#include <stdio.h>
#include <math.h>


float my_exp_func(float x, float eps);

int main()
{
    float x, eps;
    float std_exp; ///< standard lirary exponent
    float my_exp; ///< my exponent
    float abs_err; ///< absolute error between two
    ///< relative error with respect to std_exp
    float rel_err; 

    // printf("Input x, eps\n");
    if (scanf("%f %f", &x, &eps) != 2)
    {
        printf("Input Error\n");
        return 1;
    }
    if (eps <= 0)
    {
        printf("Eps should be positive\n");
        return 1;
    }

    std_exp = expf(x);
    my_exp = my_exp_func(x, eps);
    abs_err = fabsf(std_exp - my_exp);
    rel_err = abs_err / std_exp;

    printf("std exp: %f\n", std_exp);
    printf("my exp: %f\n", my_exp);
    printf("error absolute: %f\n", abs_err);
    printf("error relative: %f\n", rel_err);
}

/*
 * My exponent function
 * @param x x to be evaluated at
 * @param eps epsilon for prescision
 * @return exponent of x
 */
float my_exp_func(float x, float eps)
{
    float n = 1; ///< current number of sequence
    float x_n = 1; ///< x to the power of n
    float result = x_n; ///< result

    while (x_n >= eps)
    {
        x_n *= x / n;
        n += 1;
        result += x_n;
    }
    return result;
}