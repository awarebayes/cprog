/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 4 лабораторной 1.
 * Бутылка воды стоит 45 копеек. Пустые бутылки сдаются по 20 копеек,
 * и на полученные деньги опять покупается вода. По введённому с клавиатуры количеству копеек
 * найти и вывести на экран наибольшее возможное количество бутылок воды, которые
 * можно купить. Циклов не использовать
 * gcc -std=c99 -Werror -Wall -lm ./lab_01_04_24/main.c -o ./bin/lab4 && ./bin/lab4
 */

#include <stdio.h>

int main()
{
    int cop;
    int error_flag = 0;
    printf("Enter number of copecks: ");
    if (scanf("%d", &cop) != 1)
    {
        printf("Input Error");
        error_flag = 1;
    }
    else
    {
        if (cop < 45)
        {
            printf("0\n");
        }
        else
        {
            cop -= 45;
            printf("%d\n", cop / 25 + 1);
        }
    }
    return error_flag;
}