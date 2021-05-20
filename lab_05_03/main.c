#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.c"

/*
 * 
 *
 *
 */

int main(int argc, char **argv)
{
    int ec = 0;
    if (argc < 2)
        ec = ARG_ERROR;
    if (ec)
        return ec;
    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    if (strcmp(argv[1], "c") == 0)
    {
        int n;
        if (argc != 4)
            ec = ARG_ERROR;
        if (!ec)
        {
            n = atoi(argv[2]);
            if (n == 0) 
                ec = ARG_ERROR;
        }
        if (!ec)
            create_random_file(argv[3], n);
    }
    if (strcmp(argv[1], "p") == 0)
        ec = print_file(argv[2]);
    return ec;
}