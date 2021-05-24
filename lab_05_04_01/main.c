#include <stdio.h>
#include <string.h>
#include "student.h"
#include "futil.h"

#define OK 0
#define ARG_ERROR 53
#define FILE_ERROR 1

#define POS_BUF_LEN 256

int main(int argc, char **argv)
{
    int ec = OK;
    int buf_len = POS_BUF_LEN;
    int pos_buf[buf_len];
    for (int i = 0; i < POS_BUF_LEN; i++) 
        pos_buf[i] = i;
    if (argc == 3 && strcmp(argv[1], "sb") == 0)
    {
        FILE *file = fopen(argv[2], "rb+");
        if (!file)
            ec = FILE_ERROR;
        else
        {
            fsort(file);
            fserializef(file, stdout, pos_buf, fsize(file));
        }
        fclose(file);
    }
    else if (argc == 5 && strcmp(argv[1], "fb") == 0)
    {
        FILE *file = fopen(argv[2], "rb+");
        FILE *out = fopen(argv[3], "wb+");
        if (!file || !out)
            ec = FILE_ERROR;
        else
        {
            ffind_substr(file, argv[4], pos_buf, &buf_len);
            fserializef(file, out, pos_buf, buf_len);
        }
        fclose(file);
        fclose(out);
    }
    else if (argc == 3 && strcmp(argv[1], "db") == 0)
    {
        FILE *file = fopen(argv[2], "rb+");
        if (!file)
            ec = FILE_ERROR;
        else
        {
            f_less_mean(file, pos_buf, &buf_len);
            fdelete(argv[2], pos_buf, buf_len);
            fclose(file);
        }
    }
    else
        ec = ARG_ERROR;
    return ec;
}