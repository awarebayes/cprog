#include "futil.h"

int get_number_by_pos(FILE *file, int pos)
{
    int res;
    fseek(file, pos * sizeof(int), SEEK_SET);
    fread(&res, sizeof(int), 1, file);
    return res;
}

void set_number_by_pos(FILE *file, int pos, int num)
{
    fseek(file, pos * sizeof(int), SEEK_SET);
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
        // fwrite(&num, sizeof(int), 1, f);
        set_number_by_pos(f, i, num);
    }
    fclose(f);
}

int fprint(char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
        return NO_FILE;
    long fs = fsize(f);
    for (int i = 0; i < fs; i++)
        printf("%d ", get_number_by_pos(f, i));
    printf("\n");
    fclose(f);
    return 0;
}

void fswap(FILE *f, int p1, int p2)
{
    int a, b;
    a = get_number_by_pos(f, p1);
    b = get_number_by_pos(f, p2);
    set_number_by_pos(f, p1, b);
    set_number_by_pos(f, p2, a);
}

int fsort(char *filename)
{
    FILE *f = fopen(filename, "rb+");
    if (f == NULL)
        return NO_FILE;
    int n = fsize(f);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            if (get_number_by_pos(f, j) > get_number_by_pos(f, j + 1))
                fswap(f, j, j + 1);
    fclose(f);
    return 0;
}