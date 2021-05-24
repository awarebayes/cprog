#include "futil.h"
#include "student.h"
#include <stdio.h>
#include <string.h>

Student fget(FILE *file, int pos)
{
    Student blank;
    fseek(file, sizeof(Student) * pos, SEEK_SET);
    fread(&blank, sizeof(Student), 1, file);
    return blank;
}

void fset(FILE *file, int pos, Student *s)
{
    fseek(file, sizeof(Student) * pos, SEEK_SET);
    fwrite(s, sizeof(Student), 1, file);
}

void fswap(FILE *file, int pos1, int pos2)
{
    Student s1, s2;
    s1 = fget(file, pos1);
    s2 = fget(file, pos2);
    fset(file, pos2, &s1);
    fset(file, pos1, &s2);
}

int fcmp(FILE *file, int pos1, int pos2)
{
    Student s1, s2;
    fget(file, pos1);
    fget(file, pos2);
    
    int cmp1 = strcmp(s1.lastname, s2.lastname);
    int cmpres;
    if (cmp1 == 0)
    {
        int cmp2 = strcmp(s1.name, s2.name);
        cmpres = cmp2;
    }
    else
        cmpres = cmp1;
    return cmpres;
}

int fsize(FILE *file)
{
    fseek(file, 0, SEEK_END);
    int pos = (int)ftell(file);
    return pos / sizeof(Student);
}

void fsort(FILE *file)
{
    int size = fsize(file);
    for (int i = 0; i < size; i++)
        for (int j = 0; i < size - 1; j++)
            if (fcmp(file, j, j + 1) > 0)
                fswap(file, j, j + 1);
}

void fdelete(FILE *file, int *pos, int n_pos)
{
    FILE *temp = tmpfile();
    Student s;
    int n_deleted = 0;
    int n = fsize(file);
    
    for (int i = 0; i < n; i++)
    {
        if (n_deleted < n_pos && pos[n_deleted] == i)
            n_deleted+=1;
        else
        {
            s = fget(file, i);
            fset(temp, i-n_deleted, &s);
        }
    }

    fclose(file);
    file = fopen(file, "wb+");
    for (int i = 0; i < fsize(temp); i++)
    {
        s = fget(temp, i);
        fset(file, i, &s);
    }
}


void ffind_substr(FILE *file, char *substr, int *pos, int *n_pos)
{
    Student s;
    int cur_pos = 0;
    for (int i = 0; i < fsize(file); i++)
    {
        s = fget(file, i);
        if (strstr(s.lastname, substr) != NULL && cur_pos < *n_pos)
        {
            pos[cur_pos++] = i;
        }
    }
    *n_pos = cur_pos-1;
}