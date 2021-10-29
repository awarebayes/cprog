#ifndef __MOVIE_H__
#define __MOVIE_H__

#include <stdio.h>
#include <assert.h>

#define N_FIELDS 3

typedef struct
{
	char *title;
	char *name;
	int year;
} movie_t;

enum field_type
{
	f_title,
	f_name,
	f_year,
};

typedef union
{
	char *string;
	int number;
} field_u;


typedef struct
{
	field_u data;
	enum field_type type;
} field_t;

movie_t movie_read(FILE *f, int *ec);

void movie_print(movie_t *self);

void movie_delete(movie_t *self);

void field_from(field_t *self, movie_t *movie, int type);

int field_cmp(field_t *self, field_t *other);

int get_field_type(char *str);

field_t field_from_str(char *value, int type, int *ec);

#endif