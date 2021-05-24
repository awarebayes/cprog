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

int fsize(FILE *file, int *ec)
{
    if (file == NULL && ec)
        *ec = IO_ERROR;


    fseek(file, 0, SEEK_END);
    long n = ftell(file);
    if (ec && !*ec && n % sizeof(int))
        *ec = IO_ERROR;
    return (int)(n / sizeof(int));
}


int frcreate(FILE *f, int n)
{
    if (f == NULL)
        return FILE_ERROR;
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        int num = rand() % 1000;
        set_number_by_pos(f, i, num);
    }
    return 0;
}

int fprint(FILE *f)
{
    int ec = 0;
    long fs = fsize(f, NULL);
    for (int i = 0; i < fs; i++)
        printf("%d ", get_number_by_pos(f, i));
    printf("\n");
    return ec;
}

void fswap(FILE *f, int p1, int p2)
{
    int a, b;
    a = get_number_by_pos(f, p1);
    b = get_number_by_pos(f, p2);
    set_number_by_pos(f, p1, b);
    set_number_by_pos(f, p2, a);
}

int fsort(FILE *f)
{
    int n = fsize(f, NULL);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            if (get_number_by_pos(f, j) > get_number_by_pos(f, j + 1))
                fswap(f, j, j + 1);
    return 0;
}