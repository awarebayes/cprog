/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 9 лабораторной 1.
 * Приняв с клавиатуры по концевому признаку (до первого отрицательного числа)
 *  элементы непустой последовательности неотрицательных чисел 𝑥,
 *  вычислить и вывести на экран значение 𝑔.
 * g = sqrt(a_1 + a_2/2 + a_3/3 + ...)
 * gcc -std=c99 -Werror -Wall -lm ./lab_01_09_24/main.c -o ./bin/lab9 && ./bin/lab9
 */

#include <stdio.h>
#include <math.h>

int main()
{
    float cur = 0;
    int counter = 1;
    float sum = 0; 
    float res;

    while (1) 
    {
        if (scanf("%f", &cur) != 1)
        {
            printf("Input Error");
            return 1;
        }

        if (cur < 0)
            break;   
        
        sum += cur / counter;
        counter += 1;
    }
    res = sqrtf(sum);
    printf("%f\n", res);
}