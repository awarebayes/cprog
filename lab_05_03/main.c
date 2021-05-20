#include <stdio.h>
#include <stdlib.h>
#include "futil.h"
#include "futil.c"

#define ARG_ERROR -1
#define NO_RAND_NUMBERS -2

int main(int argc, char **argv)
{
    int ec = 0;
    if (argc < 2)
        ec = ARG_ERROR;
    if (ec)
        return ec;
    if (strcmp(argv[1], "c") == 0)
    {
        int n = atoi(argv[2]);
        if (n == 0)
            ec = NO_RAND_NUMBERS;
        if (!ec)
            frcreate(argv[1], n);
    }
    if (strcmp(argc[1], "p") == 0)
    {
    }
}
