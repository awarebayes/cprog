#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "futil.h"

#define ARG_ERROR -1

int main(int argc, char **argv)
{
    int ec = 0;
    if (argc < 2)
        ec = ARG_ERROR;
    if (!ec && strcmp(argv[1], "c") == 0 && argc == 4)
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
            frcreate(argv[3], n);
    }
    else if (!ec && strcmp(argv[1], "p") == 0 && argc == 3)
        ec = fprint(argv[2]);
    else if (!ec && strcmp(argv[1], "s") == 0 && argc == 3)
        ec = fsort(argv[2]);
    else
        ec = ARG_ERROR;
    return ec;
}
