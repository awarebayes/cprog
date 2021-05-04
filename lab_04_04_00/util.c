#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void transform(size_t n, size_t m, char *mat, char **pa)
{
    for (size_t i = 0; i < n; i++)
        pa[i] = mat + m * i;
}

void print_error(const int ec)
{
    switch (ec)
    {
        case ok:
            break;
        case string_overflow:
            printf("Error: string overflow\n");
            break;
        case input_error:
            printf("Error: input error\n");
            break;
    }
}

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