#include "movie.h"
#include "string.h"
#include <stdlib.h>
#include <ctype.h>

#define READ_ERROR 4
#define BLANK_MOVIE 5
#define TEMP_BUF_SIZE 16

static char *field_names[] = {"title", "name", "year"};

void remove_lc(char *str)
{
    str[strcspn(str, "\r\n")] = '\0';
}

int all_digits(char *str)
{
    int flag = 1;
    while (flag && *str)
    {
        if (!isdigit(*str))
            flag = 0;
        str++;
    }
    return flag;
}

int all_space(char *str)
{
    int flag = 1;
    while (flag && *str)
    {
        if (!isspace(*str))
            flag = 0;
        str++;
    }
    return flag;
}

void read_string(FILE *f, char *target, int max_target_len, int *ec)
{
    char temp_buf[TEMP_BUF_SIZE] = {0};
    fgets(target, max_target_len + 1, f);
    remove_lc(target);
    if (all_space(target))
        *ec = READ_ERROR;

    if ((int)strlen(target) == max_target_len)
    {
        fgets(temp_buf, TEMP_BUF_SIZE, f);
        remove_lc(temp_buf);
        if (strcmp(temp_buf, "") != 0)
            *ec = READ_ERROR;
    }
}

void read_year(FILE *f, int *target, int *ec)
{
    char year_buf[TEMP_BUF_SIZE] = {0};
    fgets(year_buf, TEMP_BUF_SIZE, f);
    remove_lc(year_buf);
    if (sscanf(year_buf, "%d", target) != 1)
        *ec = READ_ERROR;
}

movie_t read_movie(FILE *f, int *ec)
{
    movie_t m = {0};

    read_string(f, m.title, MAX_TITLE_LEN, ec);
    if (feof(f) && strcmp(m.title, "") == 0)
        *ec = BLANK_MOVIE;
    else
    {
        read_string(f, m.name, MAX_LN_LEN, ec); 
        read_year(f, &m.year, ec);
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
    field_t self = {0};
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

// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com