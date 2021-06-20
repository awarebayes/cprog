#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

// Почему 258:
// 256 + '\n' + '\0'
#define MSTRLEN 258

int ip_addr_valid(char *str);
void reset_values(int *value, int *digits, int *succeding_values, int *ten_power);
void process_digit(int digit, int *value, int *ten_power, int *digits, int *valid);

int main()
{
    int ec = ok;
    char str_arr[MSTRLEN];
    char *str = str_arr;

    if (!fgets(str, MSTRLEN, stdin))
        ec = input_error;

    if (strchr(str, '\0') == str + MSTRLEN - 1 && str[MSTRLEN-2] != '\n')
        ec = string_overflow;
    
    if (!ec)
    {
        str = strstrip(str);
        if (ip_addr_valid(str))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return ec;
}

int ip_addr_valid(char *str)
{
    int value = 0;
    int ten_power = 1;
    int succeding_values = 0;
    int digits = 0;
    int valid = 1;
    int n = strlen(str) - 1;

    while (n >= 0 && valid)
    {
        if (str[n] == '.')
        {
            if (value >= 256 || digits == 0 || digits > 3)
                valid = 0;
            else
                reset_values(&value, &digits, &succeding_values, &ten_power);
        }
        else if (isdigit(str[n]))
        {
            int digit = char_to_int(str[n]);
            process_digit(digit, &value, &ten_power, &digits, &valid);
        }
        else
            valid = 0;
        n--;
    }
    if (value <= 255 && digits > 0 && digits <= 3)
        succeding_values++;
    if (succeding_values != 4)
        valid = 0;
    return valid;
}

void reset_values(int *value, int *digits, int *succeding_values, int *ten_power)
{
    *value = 0;
    *digits = 0;
    *succeding_values += 1;
    *ten_power = 1;
}

void process_digit(int digit, int *value, int *ten_power, int *digits, int *valid)
{
    if (digit >= 0)
    {
        *value += (*ten_power) * digit;
        *digits += 1;
        *ten_power *= 10;
    }
    else
        *valid = 0;
}