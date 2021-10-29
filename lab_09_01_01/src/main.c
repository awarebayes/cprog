#include <stdio.h>
#include "movie.h"
#include "movie_vector.h"
#include "util.h"

int main(int argc, char **argv)
{
	int ec = ok;
	vector_t movies = { 0 };
	FILE *f = NULL;
	int field_type;
	int movies_len = 0;

	if (argc != 3 && argc != 4)
		ec = arg_error;

	if (!ec)
		f = fopen(argv[1], "r");

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
		movies = read_all_movies(f, field_type, &ec);
	}

	if (!ec)
	{
		if (argc == 3)
			vector_print(&movies);
		else
		{
			field_t field = field_from_str(argv[3], field_type, &ec);
			if (!ec)
			{
				int index = vector_find(&movies, movies_len, &field, field_type);
				if (index < 0)
					printf("Not found\n");
				else
					movie_print(vector_get(&movies, index));
			}
		}
	}
	if (f != NULL)
		fclose(f);
	vector_delete(&movies);
	return ec;
}
