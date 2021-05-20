#include "futil.h"

int fget(FILE *file, int pos)
{
    int res;
    fseek(file, pos, SEEK_SET);
    fread(&res, sizeof(int), 1, file);
    return res;
}

void fset(FILE *file, int pos, int num)
{
    fseek(file, pos, SEEK_SET);
    fwrite(&num, sizeof(int), 1, file);
}

int fsize(FILE *file)
{
    fseek(file, 0, SEEK_END);
    long n = ftell(file);
    return (int)(n / sizeof(int));
}


void frcreate(char *filename, int n)
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