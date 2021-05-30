#ifndef _FUTIL_H_
#define _FUTIL_H_

#include <stdio.h>
#include "student.h"

student_t fget(FILE *file, int pos);
void fset(FILE *file, int pos, student_t *s);
void fswap(FILE *file, int pos1, int pos2);
int fcmp(FILE *file, int pos1, int pos2);
int fsize(FILE *file);
void fsort(FILE *file);
void fdelete(char *filename, int *pos, int n_pos);
void ffind_substr(FILE *file, char *substr, int *pos, int *n_pos);
void fserializef(FILE *from, FILE *to, int *pos, int n_pos);
void f_less_mean(FILE *file, int *pos, int *n_pos);
int file_invalid(FILE *file);
int file_invalid_mb_empty(FILE *file);
int fempty(FILE *file);
void ffilter(FILE *in, FILE *out, int n, int *indices);
void fdump(char *filename, int n, student_t *students);

#endif