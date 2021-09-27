#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/util.h"

int main(int argc, char **argv)
{
    int ec = ok;
    int *arr = NULL;
    int filter_flag = 0;
    int n = 0;

    FILE *f_in = NULL;
    FILE *f_out = NULL;

    if (argc != 3 && argc != 4)
        ec = arg_err;

    if (!ec)
    {
        f_in = fopen(argv[1], "r");
        f_out = fopen(argv[2], "w");
    }
    
    if (!f_in || !f_out)
        ec = path_err;
    
    if (argc == 4)
    {
        if (strcmp(argv[3], "f") == 0)
            filter_flag = 1;
        else
            ec = arg_err;
    }

    if (!ec)
    {
        arr = read_numbers(f_in, &n, &ec);
        if (n == 0)
            ec = read_err;
    }

    if (!ec && filter_flag)
    {
        int *res_begin = NULL;
        int *res_end = NULL;
        key(arr, arr + n, &res_begin, &res_end);
        free(arr);
        arr = res_begin;
        n = res_end - res_begin;
        if (n == 0)
            ec = empty_arr_err;
    }

    if (!ec)
    {
        mysort(arr, n, sizeof(n), int_cmp);
        write_arr(arr, n, f_out);
    }

    if (f_in)
        fclose(f_in);
    
    if (f_out)
        fclose(f_out);

    if (arr)
        free(arr);

    return ec;
}
