#include <stdio.h>
#include <stdlib.h>
#include "futil.h"
#include "futil.c"

#define ARG_ERROR -1

int main(int argc, char **argv)
{
    int ec = 0;
    if (argc < 2)
        ec = ARG_ERROR;
    if (ec)
        return ec;
    if (strcmp(argv[1], "c") == 0)
    {
        int n = atoi(argv[2]);

    }
}

void create_random_file(char *filename, int n)
{
    FILE* f = fopen(filename, "wb");
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        int num = rand() % 1000;
        fset(f, i, num);
    }
    fclose(f);
}

void fprint(char *filename)
{
    FILE *f = fopen(filename, "rb");
    long fs = fsize(f);
    for (int i = 0; i < fs; i++)
        printf("%d ", fget(f, i));
    fclose(f);
}

void fswap(FILE *f, int p1, int p2)
{
    int a, b;
    a = fget(f, p1);
    b = fget(f, p2);
    fset(f, p1, b);
    fset(f, p2, a);
}

void fsort(char *filename)
{
    FILE *f = fopen(filename, "rb");
    int n = fsize(f);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n-1; j++)
            if (fget(f, j) > fget(f, j+1))
                fswap(f, j, j+1);
}