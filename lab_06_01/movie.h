#ifndef __MOVIE_H__
#define __MOVIE_H__

#include <stdio.h>
#include <assert.h>

#define MAX_TITLE_LEN 25
#define MAX_LN_LEN 25

typedef struct {
    char title[MAX_TITLE_LEN + 1];
    char name[MAX_LN_LEN + 1];
    int year;
} movie_t;

enum field_type
{
    f_title,
    f_name,
    f_year,
};

typedef union {
    char *string;
    int number;
} field_u;


typedef struct {
    field_u data;
    enum field_type type;
} field_t;

movie_t read_movie(FILE *f);
void print_movie(movie_t *m);
void field_get(field_t *self, movie_t *movie, int type);
int field_cmp(field_t self, field_t other);

#endif