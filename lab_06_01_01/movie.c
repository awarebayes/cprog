#include "movie.h"
#include "string.h"
#include <stdlib.h>
#include <ctype.h>

#define READ_ERROR 4
#define BLANK_MOVIE 5
#define YEAR_SIZE 16

static char *field_names[] = { "title", "name", "year" };

void remove_lc(char *str) 
{
    str[strcspn(str, "\r\n")] = '\0';
}

int all_digits(char *str)
{
    int flag = 1;
    while (flag && *str)
    {
        if(!isdigit(*str))
            flag = 0;
        str++;
    }
    return flag;
}

movie_t read_movie(FILE *f, int *ec) 
{
    char year_buf[YEAR_SIZE];
    movie_t m = { 0 };
    fgets(m.title, MAX_TITLE_LEN + 1, f);
    if (feof(f) && strcmp(m.title, "") == 0)
    {
        *ec = BLANK_MOVIE;
    }

    if (!*ec)
    {
        remove_lc(m.title);
        // /r/n was not read, just put it into yearbuffer
        if (strlen(m.title) == MAX_TITLE_LEN)
            fgets(year_buf, YEAR_SIZE, f);

        fgets(m.name, MAX_LN_LEN + 1, f);
        remove_lc(m.name);
        
        // /r/n was not read, just put it into yearbuffer
        if (strlen(m.name) == MAX_LN_LEN)
            fgets(year_buf, YEAR_SIZE, f);

        fgets(year_buf, YEAR_SIZE, f);
        remove_lc(year_buf);

        if (sscanf(year_buf, "%d", &m.year) != 1 || !all_digits(year_buf))
        {
            *ec = READ_ERROR;
        }
    }

    return m;
}

int string_cmp(char *haystack, char *needle) 
{
    return strcmp(haystack, needle);
}

int int_cmp(int i1, int i2)
{
    return i1 - i2;
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
                *ec = READ_ERROR;
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

void print_movie(movie_t *m) 
{
    printf("%s\n%s\n%d\n", m->title, m->name, m->year);
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