#include "movie.h"
#include "string.h"
#include <stdlib.h>

static char *field_names[] = {"title", "name", "year" };

void remove_lf(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

movie_t read_movie(FILE *f) 
{
    char year_buf[16]; // todo replace 16
    movie_t m = {0};
    fgets(m.title, MAX_TITLE_LEN, f);
    fgets(m.name, MAX_LN_LEN, f);
    fgets(year_buf, 16, f);
    sscanf(year_buf, "%d", &m.year);
    remove_lf(m.title);
    remove_lf(m.name);
    return m;
}

int string_cmp(char *haystack, char *needle) 
{
    return strncmp(needle, haystack, strlen(needle));
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

field_t field_from_str(char *value, int type)
{
    field_t self = {0};
    self.type = type;
    switch (type)
    {
    case f_name:
    case f_title:
        self.data.string = value;
        break;
    case f_year:
        sscanf(value, "%d", &self.data.number); // todo error handling
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


int get_field_index(char *str) {
    int flag = 0;
    for (int i = 0; i < N_FIELDS && !flag; i++)
    {
        if (strcmp(str, field_names[i]) == 0)
            return i;
    }
    return -1;
}