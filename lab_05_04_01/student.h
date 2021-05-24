#ifndef _STUDENT_H_
#define _STUDENT_H_

#define MIN_SERIALIZE_SYM 64
#define N_GRADES 4

typedef struct
{
    char lastname[25];
    char name[10];
    unsigned int grades[N_GRADES];
} student_t;

int serialize(student_t *s, int size, char *buf);
float mean_grade(student_t *s);

#endif