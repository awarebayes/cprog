#include <stdio.h>
#include "movie.h"
#include "movie_arr.h"


enum errors
{
    ok,
    arg_error,
};



int main() {
    
    //if (argc != 3 || argc != 4) {
    //    return arg_error;
    // }

    FILE *f = fopen("./movies.txt", "r");
    movie_t movies[MAX_MOVIES_LEN];
    int mode = f_title;
    int movies_len = read_all_movies(f, movies, mode);
    for (int i = 0; i < movies_len; i++)
        print_movie(movies + i);
}
