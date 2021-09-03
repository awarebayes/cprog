#include "movie.h"
#include "string.h"
#include <stdlib.h>

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

int string_cmp(char *s1, char *s2) 
{
    return strcmp(s1, s2);
}

int int_cmp(int i1, int i2)
{
    if (i1 >= i2)
        return -1;
    else if (i1 == i2)
        return 0;
    return 1;
}

void field_get(field_t *self, movie_t *movie, int type)
{
    field_t to_cmp;
    switch (type)
    {
        case f_name:
            to_cmp.data.string = movie->name;
            break;
        case f_title:
            to_cmp.data.string = movie->title;
            break;
        case f_year:
            to_cmp.data.number = movie->year;
            break;
    }
    *self = to_cmp;
}

int field_cmp(field_t self, field_t other)
{
    assert(self.type == other.type);
    if (self.type == f_name || other.type == f_title)
        return string_cmp(self.data.string, other.data.string);
    else
        return int_cmp(self.data.number, other.data.number);
}

void print_movie(movie_t *m) 
{
    printf("movie: %s by %s (%d)\n", m->title, m->name, m->year);
}

