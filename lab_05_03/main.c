#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "futil.h"

#define ARG_ERROR -1

int main(int argc, char **argv)
{
    int ec = 0;
    if (argc == 4 && strcmp(argv[1], "c") == 0)
    {
        int n = atoi(argv[2]);
        if (n == 0) 
            ec = ARG_ERROR;
        FILE* f = fopen(argv[3], "wb");
        if (f == NULL)
            ec = FILE_ERROR;
        fsize(f, &ec);
        if (!ec)
            ec = frcreate(f, n);
        if (ec != FILE_ERROR)
            fclose(f);
    }
    else if (argc == 3 && strcmp(argv[1], "p") == 0)
    {
        FILE *f = fopen(argv[2], "rb");
        if (f == NULL)
            ec = FILE_ERROR;
        fsize(f, &ec);
        if (!ec)
            ec = fprint(f);
        if (ec != FILE_ERROR)
            fclose(f);
    }
    else if (argc == 3 && strcmp(argv[1], "s") == 0)
    {
        FILE *f = fopen(argv[2], "rb+");
        if (f == NULL)
            ec = FILE_ERROR;
        fsize(f, &ec);
        if (!ec)
            ec = fsort(f);
        if (ec != FILE_ERROR)
            fclose(f);
    }
    else
        ec = ARG_ERROR;
    return ec;
}
