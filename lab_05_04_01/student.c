#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int serialize(student_t *s, int size, char *buf)
{
    if (size < (int)(MIN_SERIALIZE_SYM * sizeof(char)))
        return 1;
    int n;
    n = sprintf(buf, "%s\n", s->lastname);
    buf += n;
    
    n = sprintf(buf, "%s\n", s->name);
    buf += n;

    for (int i = 0; i < N_GRADES; i++)
    {
        n = sprintf(buf, "%d\n", s->grades[i]);
        buf += n;
    }
    sprintf(buf, "\n");
    return 0;
}

float mean_grade(student_t *s)
{
    float sum = 0;
    for (int i = 0; i < N_GRADES; i++)
    {
        sum += s->grades[i];
    }
    return sum / N_GRADES;
}