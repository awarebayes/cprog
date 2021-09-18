#include "util.h"

#include <stdlib.h>

int *read_numbers(FILE *f, int *n, int *ec)
{
    *n = 0;
    int temp;
    while (!feof(f))
    {
        if (fscanf(f, "%d", &temp) != 1)
            *ec = read_err;
        *n += 1;
    }

    rewind(f);

    int *buf = malloc(sizeof(int) * (*n));
    if (buf == NULL)
        *ec = malloc_err;

    int i = 0;
    while (!feof(f))
    {
        fscanf(f, "%d", buf+i);
        i++;
        // timed buffer overflow can be used here?
    }

    return buf;
}

void print_arr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", *(arr + i));
    }
}
