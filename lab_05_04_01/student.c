#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int serialize(Student *s, int size, char *buf)
{
    if (size < (int)(MIN_SERIALIZE_SYM * sizeof(char)))
        return 1;
    int n;
    n = sprintf(buf, "%s\n", s->lastname);
    buf += n;
    
    n = sprintf(buf, "%s\n", s->name);
    buf += n;

    for (int i = 0; i < (int)(sizeof(s->grades)/sizeof(int)); i++)
    {
        n = sprintf(buf, "%d ", s->grades[i]);
        buf += n;
    }
    *(buf+1) = '\n';
    *(buf+2) = '\0';
    return 0;
}