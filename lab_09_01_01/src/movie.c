#include "movie.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


static char *field_names[] = { "title", "name", "year" };

movie_t movie_read(FILE *f, int *ec)
{
	movie_t m = { 0 };

	read_string(f, &m.title, ec);
	if (m.title == NULL)
		*ec = blank_movie;
	else
	{
		read_string(f, &m.name, ec);
		read_year(f, &m.year, ec);
	}
	return m;
}

void movie_delete(movie_t *self)
{
	free(self->title);
	free(self->name);
	self->title = NULL;
	self->name = NULL;
}

void movie_print(movie_t *self)
{
	printf("%s\n%s\n%d\n", self->title, self->name, self->year);
}

void field_from(field_t *self, movie_t *movie, int type)
{
	self->type = type;
	switch (type)
	{
		case f_name:
			self->data.string = movie->name;
			break;
		case f_title:
			self->data.string = movie->title;
			break;
		case f_year:
			self->data.number = movie->year;
			break;
		default:
			break;
	}
}

field_t field_from_str(char *value, int type, int *ec)
{
	field_t self = { 0 };
	self.type = type;
	switch (type)
	{
		case f_name:
		case f_title:
			self.data.string = value;
			break;
		case f_year:
			if (sscanf(value, "%d", &self.data.number) != 1)
				*ec = read_error;
			break;
		default:
			break;
	}
	return self;
}

int field_cmp(field_t *self, field_t *other)
{
	int res = 0;
	assert(self->type == other->type);
	if (self->type == f_name || other->type == f_title)
		res = string_cmp(self->data.string, other->data.string);
	else
		res = int_cmp(self->data.number, other->data.number);
	return res;
}

int get_field_type(char *str)
{
	int flag = 0;
	int index = 0;
	for (int i = 0; i < N_FIELDS && !flag; i++)
	{
		if (strcmp(str, field_names[i]) == 0)
		{
			flag = 1;
			index = i;
		}
	}
	return flag ? index : -1;
}


// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com