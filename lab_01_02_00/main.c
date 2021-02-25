/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 2 лабораторной 1.
 * 0. Принять с клавиатуры величины оснований 𝑎 и 𝑏 и высоты h
 * равнобедренной трапеции. Найти и вывести на экран периметр 𝑃 трапеции.
 * gcc -std=c99 -Werror -Wall -lm ./lab01_02_24/main.c -o ./bin/lab2 && ./bin/lab2
 */

#include <stdio.h>
#include <math.h>

float perimiter_trapezoid(float a, float b, float h);
void print_error(int error_flag);

int main(void)
{
    float a, b, h;
    int error_flag = 0;
    printf("Input a, b, h\n");

    if (scanf("%f %f %f", &a, &b, &h) != 3)
        error_flag = 1;
    else
    {
        float perimeter = perimiter_trapezoid(a, b, h);
        printf("%f\n", perimeter);
    }
    print_error(error_flag);
    return error_flag;
}

/*
 * Perimeter of a trapezoid
 */
float perimiter_trapezoid(float a, float b, float h)
{
    float j = fabs(a - b) / 2;
    float perimeter = 2 * sqrt(j * j + h * h) + a + b;
    return perimeter;
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