/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 8 лабораторной 1.
 * Вводятся беззнаковое целое число длиной 4 байта 𝑎 и целое число 𝑛.
 * Числа вводятся в десятичной системе счисления. Необходимо циклически сдвинуть значение
 * переменной 𝑎 на 𝑛 позиций вправо. Результат вывести в двоичной системе счисления.
 * gcc -std=c99 -Werror -Wall -Wfloat-equal -Wfloat-conversion -lm ./lab_01_08_00/main.c -o ./bin/lab8 && ./bin/lab8
 */

#include <stdio.h>
#include <stdint.h>

void print_bin(unsigned long number, int remaining);
unsigned long shift_left(unsigned long number, int n);
unsigned long shift_right(unsigned long number, int n);

int main()
{
    uint32_t a; ///< number to shift
    int n; ///< positions to shift

    printf("Input a and n\n");
    if (scanf("%u %d", &a, &n) != 2)
    {
        printf("Error: Input was wrong\n");
        return 1;
    }

    if (n >= 0)
    {
        a = shift_right(a, n);
    }
    else
    {
        n *= -1;
        a = shift_left(a, n);
        //printf("Input Error");
        //return 1;
    }

    printf("Result: ");
    print_bin(a, 32);
    printf("\n");
}

/*
 * Print a binary number
 * @param number number to print
 * @param remaining number of BITS remaining to print
 */
void print_bin(unsigned long number, int remaining)
{
    if (remaining == 0)
        return;
    print_bin(number >> 1, remaining - 1);
    putc((number & 1) ? '1' : '0', stdout);
}

/*
 * Cyclically shift number n times
 * @param number to shift
 * @param n times to shift shift right 
 * @return shifted number
 */
unsigned long shift_right(unsigned long number, int n)
{
    n = n % 32;
    for (int i = 0; i < n; i++)
    {
        uint32_t first_bit = number & 1;
        number = number >> 1;
        number = number | (first_bit << 31);
    }
    return number;
}

/*
 * Cyclically shift number n times
 * @param number to shift
 * @param n times to shift shift right 
 * @return shifted number
 */
unsigned long shift_left(unsigned long number, int n)
{
    n = n % 32;
    for (int i = 0; i < n; i++)
    {
        uint32_t last_bit = number >> 31;
        number = (number << 1) | last_bit;
    }
    return number;
}

