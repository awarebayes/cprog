#include <stdio.h>
#include "student.h"
#include "student.c"
#include "futil.c"

#define OK 0
#define ARG_ERROR 53

int main()
{
    Student a = { "Scherbina", "Mikhail", {1, 2, 3, 4}};
    Student b = { "Scherbina", "Aleksandr", {1, 3, 4, 5}};
    Student c = { "Pavel", "Ivanov", {1, 3, 4, 5}};
    Student d = { "Vladimir", "Khudyakov", {1, 3, 4, 5}};
    Student d = { "Runov", "Konstantin", {1, 3, 4, 5}};
    Student d = { "Runov", "Konstantin", {1, 3, 4, 5}};
    FILE *file = fopen("./temp/a", "wb");
    fset(file, 0, &a);
    fset(file, 1, &b);
    fset(file, 2, &c);
    fset(file, 3, &d);
    fclose(file);
}