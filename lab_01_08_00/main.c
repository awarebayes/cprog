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

void print_bin(uint32_t number, int remaining);
uint32_t shift_right(uint32_t number, int n);
void print_error(int error_flag);

int main()
{
    uint32_t a; ///< number to shift
    int n; ///< positions to shift
    int error_flag = 0;

    printf("Input a and n\n");
    if (scanf("%u %d", &a, &n) != 2)
        error_flag = 1;
    else if (n < 0)
        error_flag = 2;
    else
    {
        a = shift_right(a, n);
        printf("Result: ");
        print_bin(a, 32);
        printf("\n");
    }
    print_error(error_flag);
    return error_flag;
}

/*
 * Print a binary number
 * @param number number to print
 * @param remaining number of BITS remaining to print
 */
void print_bin(uint32_t number, int remaining)
{
    uint32_t mask = 1 << (remaining-1);
    while (mask > 0){
        putc((number & mask) ? '1' : '0', stdout);
        mask = mask >> 1;
    }
}

/*
 * Cyclically shift number n times
 * @param number to shift
 * @param n times to shift shift right 
 * @return shifted number
 */
uint32_t shift_right(uint32_t number, int n)
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

void print_error(int error_flag)
{
    switch (error_flag)
    {
        case 1:
            printf("Error: Input Error\n");
            break;
        case 2:
            printf("Error: n should be positive\n");
            break;
        default:
            break;
    }
}