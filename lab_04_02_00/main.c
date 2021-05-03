#include <stdio.h>
#include <string.h>
#include "split.c"
#include "count.c"

#define MSLEN 256 // MaxStringLen
#define MWORDS 128 // MaxWords in string
#define MWORDLEN 16 // MaxWordLen

int read_line(char *s, int n, int *ec);
void print_error(const int ec);

enum ec
{
    ok,
    no_words,
    string_overflow,
    long_word,
};

int main()
{
    int ec = ok;
    char line[MSLEN];
    int line_len;

    line_len = read_line(line, MSLEN, &ec);
    char words[MWORDS][MWORDLEN];
    char *pa[MWORDS];

    transform(MWORDS, MWORDLEN, *words, pa);
    int n_words;

    n_words = split(pa, line, line_len, &ec);
    if (!ec)
    {
        if (n_words == 0 || line_len == 0)
            ec = no_words;
        else
            print_word_count(pa, n_words);
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

