#include <stdio.h>
#include <stdlib.h>

#define ARG_ERROR -1

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

    }
}

void create_random_file(char *filename, int n)
{
    FILE* f = fopen(filename, "w");
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        int num = rand() % 1000;
        fprintf(f, "%d ", num);
    }
    fclose(f);
}