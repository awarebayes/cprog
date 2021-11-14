#ifndef __MOVIE_ARR__
#define __MOVIE_ARR__

#include <stdio.h>
#include "movie.h"

#define MAX_MOVIES_LEN 15

void arr_insert(movie_t *arr, movie_t *m, int pos);
int arr_find(movie_t *arr, int n, field_t *target, int mode);
int read_all_movies(FILE *f, movie_t *in, int mode, int *ec);
void print_movie_arr(movie_t *arr, int n);

#endif

// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com