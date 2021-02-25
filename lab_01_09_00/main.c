/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 9 лабораторной 1.
 * Приняв с клавиатуры по концевому признаку (до первого отрицательного числа)
 *  элементы непустой последовательности неотрицательных чисел 𝑥,
 *  вычислить и вывести на экран значение 𝑔.
 * g = sqrt(a_1 + a_2/2 + a_3/3 + ...)
 * gcc -std=c99 -Werror -Wall -lm ./lab_01_09_00/main.c -o ./bin/lab9 && ./bin/lab9
 */

#include <stdio.h>
#include <math.h>

int main()
{
    float cur = 0;
    int counter = 1;
    float sum = 0; 
    float res;
    int error_flag = 0;

    while (1) 
    {
        if (scanf("%f", &cur) != 1)
        {
            error_flag = 1;
            break;
        }
        else if (cur < 0)
            break;   
        else
        {
            sum += cur / counter;
            counter += 1;
        }
    }
    if (!error_flag)
        res = sqrtf(sum);
    print_error(error_flag);
    return error_flag;
}

void print_error(int error_flag)
{
    switch (error_flag)
    {
        case 1:
            printf("Input Error\n");
            break;
        default:
            break;
    }
}