#ifndef __MOVIE_ARR__
#define __MOVIE_ARR__

#include <stdio.h>
#include "movie.h"

#define MAX_MOVIES_LEN 15

void arr_insert(movie_t *arr, movie_t *m, int pos);
int arr_find_str(movie_t *arr, int n, char *target, int mode);
int read_all_movies(FILE *f, movie_t *in, int mode);

#endif