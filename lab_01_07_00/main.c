/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 7 лабораторной 1.
 * Приняв с клавиатуры 𝑥 и 𝜀, вычислить и вывести на экран вычисленное с точностью E
 * приближённое значение 𝑠(𝑥) и точное значение 𝑓(𝑥) функции 𝑓,
 * абсолютную ∆ и относительную 𝛿 погрешности:
 * Мой вариант: exp(x)
 * gcc -std=c99 -Werror -Wall  -lm ./lab_01_07_00/main.c -o ./bin/lab7 && ./bin/lab7
 */

#include <stdio.h>
#include <math.h>


float my_exp_func(float x, float eps);
void print_results(float std_exp, float my_exp, float abs_err, float rel_err);
void print_error(int error_flag);

int main()
{
    float x, eps;
    float std_exp; ///< standard lirary exponent
    float my_exp; ///< my exponent
    float abs_err, rel_err; ///< errors
    int error_flag = 0;

    // printf("Input x, eps\n");
    if (scanf("%f %f", &x, &eps) != 2)
        error_flag = 1;
    else if (eps <= 0 || eps >= 1)
        error_flag = 2;
    else
    {
        std_exp = expf(x);
        my_exp = my_exp_func(x, eps);
        abs_err = fabsf(std_exp - my_exp);
        rel_err = abs_err / std_exp;

        print_results(std_exp, my_exp, abs_err, rel_err);
    }
    print_error(error_flag);
    return error_flag;
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

void print_results(float std_exp, float my_exp, float abs_err, float rel_err)
{
    printf("%f\n", std_exp);
    printf("%f\n", my_exp);
    printf("%f\n", abs_err);
    printf("%f\n", rel_err);
}

void print_error(int error_flag)
{
    switch (error_flag)
    {
        case 1:
            printf("Input Error");
            break;
        case 2:
            printf("Eps should be in (0, 1)\n");
            break;
        default:
            break;
    }
}