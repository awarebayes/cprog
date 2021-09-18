#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main()
{

    int ec = ok;
    FILE *f = fopen("./numbers.txt", "r+");

    int n = 0;
    int *arr = read_numbers(f, &n, &ec);
    print_arr(arr, n);

    fclose(f);

    free(arr);
}