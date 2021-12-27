#include "io.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

int file_n_numbers(FILE *f, int *ec)
{
	printf("file n numbers\n");
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
	printf("I will read numbers\n");
    *n = file_n_numbers(f, ec);
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
    }

    return buf;
}

void write_arr(int *arr, int n, FILE *f)
{
	printf("I will write numbers\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d ", *(arr + i));
    }
    fprintf(f, "\n");
}