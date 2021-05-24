#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "futil.h"

#define ARG_ERROR -1

int main(int argc, char **argv)
{
    int ec = 0;
    if (argc == 5 && strcmp(argv[1], "c") == 0)
    {
        int n;
        n = atoi(argv[2]);
        if (n == 0) 
            ec = ARG_ERROR;
        if (!ec)
            ec = frcreate(argv[3], n);
    }
    else if (argc == 3 && strcmp(argv[1], "p") == 0)
        ec = fprint(argv[2]);
    else if (argc == 3 && strcmp(argv[1], "s") == 0)
        ec = fsort(argv[2]);
    else
        ec = ARG_ERROR;
    return ec;
}
