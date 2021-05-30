/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 3 лабораторной 1.
 * По введённым с клавиатуры росту человека в сантиметрах, обхвату грудной клетки в
 * сантиметрах и массе тела в килограммах определить и вывести на экран нормальный
 * вес человека 𝑚 normal и индекс массы его тела BMI, полагая, что ...
 * gcc -std=c99 -Werror -Wall -Wfloat-equal -Wfloat-conversion \
   -lm ./lab_01_03_24/main.c -o ./bin/lab3 && ./bin/lab3
 */

#include <stdio.h>

void print_error(int error_flag);
void calculate(float height, float chest, float mass,
float *weight_normal, float *bmi);

int main()
{
    float height, chest, mass;
    float weight_normal, bmi;
    int error_flag = 0;

    printf("Input height, chest diameter, mass: \n");
    if (scanf("%f %f %f", &height, &chest, &mass) != 3 ||
        height <= 0 || chest <= 0 || mass <= 0)
        error_flag = 1;

    printf("%f\n", weight_normal);
    printf("%f\n", bmi);

    calculate(height, chest, mass, &weight_normal, &bmi);

    print_error(error_flag);
    return error_flag;
}

void calculate(float height, float chest, float mass,
float *weight_normal, float *bmi)
{
    *weight_normal = height * chest / 240.0;
    height /= 100.0;
    *bmi = mass / (height * height);
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