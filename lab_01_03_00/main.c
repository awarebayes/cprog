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

int main()
{
    float height, chest, mass;
    float weight_normal, bmi;

    printf("Input height, chest diameter, mass: \n");
    if (scanf("%f %f %f", &height, &chest, &mass) != 3 ||
        height <= 0 || chest <= 0 || mass <= 0)
    {
        printf("Input Error");
        return 1;
    }

    weight_normal = height * chest / 240;
    bmi = mass / (height * height);

    printf("%f\n", weight_normal);
    printf("%f\n", bmi);

    return 0;
}