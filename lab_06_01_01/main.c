#include <stdio.h>
#include "movie.h"
#include "movie_arr.h"


enum errors
{
    ok,
    arg_error,
    path_error,
    field_type_error,
};

int main(int argc, char **argv) {

    movie_t movies[MAX_MOVIES_LEN];

    if (argc != 3 && argc != 4) {
        return arg_error;
    }  

    FILE *f = fopen(argv[1], "r");
    if (!f)
        return path_error;

    char *field_name = argv[2];
    int field_type = get_field_type(field_name);
    if (field_type < 0)
        return field_type_error;
    int movies_len = read_all_movies(f, movies, field_type);

    if (argc == 3)
    {
        for (int i = 0; i < movies_len; i++)
            print_movie(movies + i);
    }
    else
    {
        field_t field = field_from_str(argv[3], field_type);
        int index = arr_find(movies, movies_len, &field, field_type);
        if (index < 0)
            printf("Not found\n");
        else
            print_movie(movies + index);
    }
}
