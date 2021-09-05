#include "movie_arr.h"
#include <string.h>
#include <stdlib.h>

void shift_arr_right(movie_t *movie_arr, int from)
{
    if (from >= MAX_MOVIES_LEN) {
        perror("Bad from in shift arr\n");
        exit(-1);
    }

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
    field_t target = {0};
    field_t to_cmp = {0};
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

    while (low <= high)
    {
        mid = (low + high - 1) / 2;
        field_from(&to_cmp, arr + mid, mode);
        if (field_cmp(&to_cmp, target) == 0)
            return mid;
        else if (field_cmp(&to_cmp, target) < 0)
            low = mid + 1;
        else if (field_cmp(&to_cmp, target) > 0)
            high = mid - 1;
    }
    return -1;
}

int read_all_movies(FILE *f, movie_t *in, int mode) 
{
    int count = 0;
    movie_t m;
    while (!feof(f))
    {
        m = read_movie(f);
        arr_insert_sorted(in, count, &m, mode);
        count++;
    }
    return count;
}
