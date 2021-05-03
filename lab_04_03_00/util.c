#include <stdio.h>
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
        case no_words:
            printf("Error: no words in line\n");
            break;
        case string_overflow:
            printf("Error: string overflow\n");
            break;
        case long_word:
            printf("Error: long word\n");
            break;
        case no_words_remaining:
            printf("Error: no words remaining\n");
            break;
    }
}

int read_line(char *s, int n, int *ec)
{
    int ch, i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
        else
            *ec = string_overflow;
    s[i] = '\0';
    return i;
}

