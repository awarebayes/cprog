#include <stdio.h>

#include "../../student.h"
#include "../../student.c"
#include "../../futil.c"

int main()
{

    student_t a = { "Sherbina", "Mikhail", { 1,2,3,4 } };
    student_t b = { "Sherbina", "Aleksandr", { 1,2,3,4 } };
    student_t c = { "Aboba", "Aboba", {0,0,0,0} };
    student_t students[3];
    students[0] = a;
    students[1] = b;
    students[2] = c;
    fdump("../a", 3, students);
}