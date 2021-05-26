#include <stdio.h>
#include <string.h>
#include "student.h"
#include "futil.h"

student_t fget(FILE *file, int pos)
{
    student_t blank = { 0 };
    fseek(file, sizeof(student_t) * pos, SEEK_SET);
    fread(&blank, sizeof(student_t), 1, file);
    return blank;
}

void fset(FILE *file, int pos, student_t *s)
{
    fseek(file, sizeof(student_t) * pos, SEEK_SET);
    fwrite(s, sizeof(student_t), 1, file);
}

void fswap(FILE *file, int pos1, int pos2)
{
    student_t s1 = { 0 }, s2= { 0 };
    s1 = fget(file, pos1);
    s2 = fget(file, pos2);
    fset(file, pos2, &s1);
    fset(file, pos1, &s2);
}

int fcmp(FILE *file, int pos1, int pos2)
{
    student_t s1 = { 0 }, s2 = { 0 };
    s1 = fget(file, pos1);
    s2 = fget(file, pos2);
    
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
    return pos / sizeof(student_t);
}

void fsort(FILE *file)
{
    int size = fsize(file);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - 1; j++)
            if (fcmp(file, j, j + 1) > 0)
                fswap(file, j, j + 1);
}

void fdelete(char *filename, int *pos, int n_pos)
{
    FILE *file = fopen(filename, "rb");
    FILE *temp = tmpfile();
    student_t s = { 0 };
    int n_deleted = 0;
    int n = fsize(file);
    
    for (int i = 0; i < n; i++)
    {
        if (n_deleted < n_pos && pos[n_deleted] == i)
            n_deleted += 1;
        else
        {
            s = fget(file, i);
            fset(temp, i - n_deleted, &s);
        }
    }

    fclose(file);
    file = fopen(filename, "wb");
    for (int i = 0; i < fsize(temp); i++)
    {
        s = fget(temp, i);
        fset(file, i, &s);
    }
}


void ffind_substr(FILE *file, char *substr, int *pos, int *n_pos)
{
    student_t s = { 0 };
    int cur_pos = 0;
    for (int i = 0; i < fsize(file); i++)
    {
        s = fget(file, i);
        if (strstr(s.lastname, substr) != NULL && cur_pos < *n_pos)
        {
            pos[cur_pos++] = i;
        }
    }
    *n_pos = cur_pos; // WATCH
}

void fserializef(FILE *from, FILE *to, int *pos, int n_pos)
{
    char buf[128];
    student_t s = { 0 };
    for (int i = 0; i < n_pos; i++)
    {
        s = fget(from, pos[i]); 
        serialize(&s, sizeof(buf), buf);
        fprintf(to, "%s", buf);
    }
}

void f_less_mean(FILE *file, int *pos, int *n_pos)
{
    float mean = 0;
    float sum = 0;
    student_t s = { 0 };
    int n = fsize(file);
    for (int i = 0; i < n; i++)
    {
        s = fget(file, i);
        sum += mean_grade(&s);
    }
    mean = sum / n;
    
    int cur_pos = 0;
    for (int i = 0; i < n; i++)
    {
        s = fget(file, i);
        float grade = mean_grade(&s);
        if (grade < mean && *n_pos > cur_pos)
        {
            pos[cur_pos] = i;
            cur_pos += 1;
        }
    }
    *n_pos = cur_pos;
}

int file_invalid(FILE *file)
{
    if (file == NULL)
        return 1;
    fseek(file, 0, SEEK_END);
    int res = ftell(file) % sizeof(student_t);
    res = res & fempty(file);
    return res;
}

int fempty(FILE *file)
{
    fseek(file, 0, SEEK_END);
    return ftell(file);
}

void fdump(char *filename, int n, student_t *students)
{
    FILE *file = fopen(filename, "wb");
    for (int i = 0; i < n; i++)
    {
        fset(file, i, &students[i]);
    }
    fclose(file);
}