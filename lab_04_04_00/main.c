#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define MSTRLEN 255

char *strstrip(char *s)
{
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;
    return s;
}

int char_to_int(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    return -1;
}

int ip_addr_valid(char *str)
{
    int n = 0;
    int value = 0;
    int ten_power = 1;
    int succeding_values = 0;
    int digits = 0;

    n = strlen(str) - 1;

    int valid = 1;

    while (n >= 0 && valid)
    {
        if (str[n] == '.')
        {
            // check value
            if (value >= 256 || digits == 0 || digits > 3)
                valid = 0;
            // reset value
            else
            {
                value = 0;
                digits = 0;
                succeding_values++;
                ten_power = 1;
            }
        }
        else if (isdigit(str[n]))
        {
            int digit = char_to_int(str[n]);
            if (digit >= 0)
            {
                value += ten_power * digit;
                digits++;
                ten_power *= 10;
            }
            else
                valid = 0;
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

int main()
{
    int ec = ok;
    char str_arr[MSTRLEN];
    char *str = str_arr;

    read_line(str_arr, MSTRLEN, &ec);
    str = strstrip(str);
    if (!ec)
    {
        if (ip_addr_valid(str))
            printf("YES\n");
        else
            printf("NO\n");
    }
    print_error(ec);
    return ec;
}