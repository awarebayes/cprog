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