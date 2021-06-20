#include <stdio.h>
#include <string.h>
#include "split.h"
#include "count.h"
#include "error.h"


int read_line(char *s, int n, int *ec);
void print_error(const int ec);

int main()
{
    int ec = ok;
    char line[MSLEN];
    int line_len = read_line(line, MSLEN, &ec);
    char words[MWORDS][MWORDLEN];
    char *pa[MWORDS];

    int n_unique = 0;
    int count[MWORDS] = { 0 };
    char unique_mat[MWORDS][MWORDLEN] = { 0 };
    char *unique[MWORDS];

    transform(MWORDS, MWORDLEN, *words, pa);
    transform(MWORDS, MWORDLEN, *unique_mat, unique);
    int n_words = split(pa, line, line_len, &ec);
    if (!ec)
    {
        if (n_words == 0 || line_len == 0)
            ec = no_words;
        else
        {
            unique_words(pa, unique, n_words, &n_unique);
            word_count(pa, unique, count, n_words, n_unique);
            print_word_count(n_unique, unique, count);
        }
    }
    print_error(ec);
    return ec;
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
    }
}

