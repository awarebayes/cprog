#include "io.h"
#include "util.h"
#include <stdlib.h>

int n_numbers(FILE *f, int *ec)
{
    int n = 0;
    int temp;
    while (!feof(f) && !(*ec))
    {
        if (fscanf(f, "%d", &temp) != 1)
            *ec = read_err;
        else
            n += 1;
    }

    rewind(f);
    return n;
}

int *read_numbers(FILE *f, int *n, int *ec)
{
    *n = n_numbers(f, ec);
    int *buf = NULL;
    if (*n > 0)
        buf = malloc(sizeof(int) * (*n));
    if (buf == NULL)
        *ec = malloc_err;

    int i = 0;
    while (!feof(f) && !(*ec))
    {
        fscanf(f, "%d", buf + i);
        i++;
        // timed buffer overflow can be used here?
    }

    return buf;
}

void write_arr(int *arr, int n, FILE *f)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d ", *(arr + i));
    }
    fprintf(f, "\n");
}