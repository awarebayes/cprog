#include <stdio.h>
#include "movie.h"
#include "movie_arr.h"

enum errors
{
    ok,
    arg_error,
    path_error,
    field_type_error,
    read_error,
    blank_movie,
    empty_file,
};

int main(int argc, char **argv)
{
    int ec = ok;
    movie_t movies[MAX_MOVIES_LEN];
    FILE *f = fopen(argv[1], "r");
    int field_type;
    int movies_len;

    if (argc != 3 && argc != 4) 
        ec = arg_error;
    
    if (!ec && !f)
        ec = path_error;

    if (!ec)
    {
        char *field_name = argv[2];
        field_type = get_field_type(field_name);
        if (field_type < 0)
            ec = field_type_error;
    }

    if (!ec)
    {
        movies_len = read_all_movies(f, movies, field_type, &ec);
        if (movies_len == 0)
            ec = empty_file;
    }

    if (!ec)
    {
        if (argc == 3)
            print_movie_arr(movies, movies_len);
        else
        {
            field_t field = field_from_str(argv[3], field_type, &ec);
            if (!ec)
            {
                int index = arr_find(movies, movies_len, &field, field_type);
                if (index < 0)
                    printf("Not found\n");
                else
                    print_movie(movies + index);
            }
        }
    }
    return ec;
}
