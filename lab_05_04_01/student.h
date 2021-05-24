#ifndef _STUDENT_H_
#define _STUDENT_H_

#define MIN_SERIALIZE_SYM 64

typedef struct
{
    char lastname[25];
    char name[10];
    unsigned int grades[4];
} Student;

#endif