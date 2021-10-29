//
// Created by dev on 10/28/21.
//

#ifndef LAB_09_01_01_UTIL_H
#define LAB_09_01_01_UTIL_H
#define _GNU_SOURCE

#define TEMP_BUF_SIZE 16

#include <ctype.h>
#include <string.h>
#include <stdio.h>

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

void remove_lc(char *str);
int all_digits(char *str);
int all_space(char *str);
void read_string(FILE *f, char **target, int *ec);
void read_year(FILE *f, int *target, int *ec);
int string_cmp(char *haystack, char *needle);
int int_cmp(int i1, int i2);

#endif //LAB_09_01_01_UTIL_H
