#include "movie_arr.h"
#include <string.h>
#include <stdlib.h>

#define BLANK_MOVIE 5
#define TOO_MANY_MOVIES 7

void shift_arr_right(movie_t *movie_arr, int from)
{
    for (int i = MAX_MOVIES_LEN - 1; i > from; i--)
    {
        movie_arr[i] = movie_arr[i - 1];
    }
}

void arr_insert(movie_t *arr, movie_t *m, int pos)
{
    shift_arr_right(arr, pos);
    arr[pos] = *m;
}

int arr_insert_sorted(movie_t *arr, int arr_size, movie_t *m, int mode)
{
    field_t target = { 0 };
    field_t to_cmp = { 0 };
    field_from(&target, m, mode);
    int index = 0;
    int flag = 1;
    for (int i = 0; i < arr_size && flag; i++)
    {
        field_from(&to_cmp, arr + i, mode);
        index = i;
        if (field_cmp(&to_cmp, &target) > 0)
            flag = 0;
        else
            index++;
    }
    arr_insert(arr, m, index);
    return arr_size + 1;
}

int arr_find(movie_t *arr, int n, field_t *target, int mode)
{
    int low = 0;
    int high = n;
    int mid;
    field_t to_cmp;
    int found = 0;

    while (low <= high && !found)
    {
        mid = (low + high) / 2;
        field_from(&to_cmp, arr + mid, mode);
        if (field_cmp(&to_cmp, target) == 0)
            found = 1;
        else if (field_cmp(&to_cmp, target) < 0 && !found)
            low = mid + 1;
        else if (field_cmp(&to_cmp, target) > 0 && !found)
            high = mid - 1;
    }
    return found ? mid : -1;
}

int read_all_movies(FILE *f, movie_t *in, int mode, int *ec) 
{
    int count = 0;
    movie_t m;
    int blank_encountered = 0;
    while (!feof(f) && !(*ec) && !blank_encountered)
    {
        m = read_movie(f, ec);
        if (*ec == BLANK_MOVIE)
            blank_encountered = 1;
        else
        {
            if (count >= MAX_MOVIES_LEN)
                *ec = TOO_MANY_MOVIES;
            else 
            {
                arr_insert_sorted(in, count, &m, mode);
                count++;
            }
        }
    }
    if (blank_encountered)
        *ec = 0;
    return count;
}

void print_movie_arr(movie_t *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        print_movie(arr + i);
    }
}