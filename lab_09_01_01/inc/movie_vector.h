#ifndef __MOVIE_ARR__
#define __MOVIE_ARR__

#include <stdio.h>
#include "movie.h"

#define MAX_MOVIES_LEN 15

typedef struct
{
	int size;
	int capacity;
	movie_t *pointer;
} vector_t;

vector_t vector_new(int capacity);
void vector_delete(vector_t *self);
movie_t *vector_get(vector_t *self, int index);
void vector_insert(vector_t *arr, movie_t *m, int pos);
int vector_find(vector_t *arr, field_t *target, int mode);
void vector_print(vector_t *self);
vector_t read_all_movies(FILE *f, int mode, int *ec);

#endif
