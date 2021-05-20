#include "util.h"

void create_random_file(char *filename, int n)
{
    FILE *f = fopen(filename, "w");
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        int num = rand() % 1000;
        fprintf(f, "%d ", num);
    }
    fclose(f);
}

int print_file(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return NO_FILE_EXISTS;
    int num = 0;
    while (!feof(f))
    {
        fscanf(f, "%d", &num);
        printf("%d ", num);
    }
    printf("\n");
    fclose(f);
    return 0;
}

int get_number_by_pos(FILE *file, int pos, int *ec)
{
    int cur = 0;
    int num = 0;
    int flag = 1;
    rewind(file);
    while (!feof(file) && flag)
    {
        fscanf(file, "%d", &cur);
        if (pos == cur)
            flag = 0;
    }
    if (!flag)
        *ec = NO_POS;
    return num;
}

int replace_number_by_pos(FILE *file, int pos, int *ec)