//
// Created by dev on 10/28/21.
//
#include "util.h"
#include <stdlib.h>

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

void read_string(FILE *f, char **target, int *ec)
{
	size_t size = 0;
	if (getline(target, &size, f) == -1)
	{
		free(*target);
		*target = NULL;
	}
	else
	{
		remove_lc(*target);
		if (all_space(*target))
			*ec = read_error;
	}
}


void read_year(FILE *f, int *target, int *ec)
{
	char year_buf[TEMP_BUF_SIZE] = { 0 };
	fgets(year_buf, TEMP_BUF_SIZE, f);
	remove_lc(year_buf);
	if (!all_digits(year_buf))
		*ec = read_error;

	if (sscanf(year_buf, "%d", target) != 1)
		*ec = read_error;
}


int string_cmp(char *haystack, char *needle)
{
	return strcmp(haystack, needle);
}

int int_cmp(int i1, int i2)
{
	return i1 - i2;
}
