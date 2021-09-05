#include "movie.h"
#include "string.h"
#include <stdlib.h>

#define READ_ERROR 4
#define BLANK_MOVIE 5
#define YEAR_SIZE 16

static char *field_names[] = { "title", "name", "year" };

void remove_lf(char *str) 
{
    str[strcspn(str, "\r\n")] = '\0';
}

movie_t read_movie(FILE *f, int *ec) 
{
    char year_buf[YEAR_SIZE];
    movie_t m = { 0 };
    fgets(m.title, MAX_TITLE_LEN + 1, f);
    if (feof(f) && strcmp(m.title, "") == 0)
    {
        *ec = BLANK_MOVIE;
        return m;
    }

    // /r/n was not read, just put it into yearbuffer
    if (strlen(m.title) == MAX_TITLE_LEN)
        fgets(year_buf, YEAR_SIZE, f);

    fgets(m.name, MAX_LN_LEN + 1, f);

    // /r/n was not read, just put it into yearbuffer
    if (strlen(m.name) == MAX_LN_LEN)
        fgets(year_buf, YEAR_SIZE, f);
    fgets(year_buf, YEAR_SIZE, f);

    if (sscanf(year_buf, "%d", &m.year) != 1)
    {
        *ec = READ_ERROR;
        return m;
    }

    remove_lf(m.title);
    remove_lf(m.name);
    return m;
}

int string_cmp(char *haystack, char *needle) 
{
    //return strncmp(needle, haystack, strlen(needle));
    return strcmp(haystack, needle);
}

int int_cmp(int i1, int i2)
{
    if (i1 > i2)
        return 1;
    else if (i1 == i2)
        return 0;
    return -1;
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
            {
                *ec = READ_ERROR;
            }
            break;
        default:
            break;
    }
    return self;
}

int field_cmp(field_t *self, field_t *other)
{
    assert(self->type == other->type);
    if (self->type == f_name || other->type == f_title)
        return string_cmp(self->data.string, other->data.string);
    else
        return int_cmp(self->data.number, other->data.number);
}

void print_movie(movie_t *m) 
{
    //printf("movie: %s by %s (%d)\n", m->title, m->name, m->year);
    printf("%s\n%s\n%d\n", m->title, m->name, m->year);
}


int get_field_type(char *str) 
{
    int flag = 0;
    for (int i = 0; i < N_FIELDS && !flag; i++)
    {
        if (strcmp(str, field_names[i]) == 0)
            return i;
    }
    return -1;
}