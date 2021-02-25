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

int main(void)
{
    float a, b, h;

    printf("Input a, b, h\n");

    if (scanf("%f %f %f", &a, &b, &h) != 3)
    {
        printf("Input Error\n");
        return 1;
    }

    float perimeter = perimiter_trapezoid(a, b, h);
    printf("%f\n", perimeter);
    return 0;
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