//
// Created by dev on 11/14/21.
//
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "util.h"

#define BUFFER_SIZE 1024

static void remove_lc(char *str)
{
	str[strcspn(str, "\r\n")] = '\0';
}

static int all_digits(char *str)
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

void read_int_array(int *out, int *size, int max_size, char *in, int *ec)
{
	int local_ec = ok;
	char *token = strtok(in, " ");
	if (*token == '\0')
		local_ec = input_err;
	int value = 0;
	*size = 0;
	while (token && !local_ec)
	{
		remove_lc(token);
		if (*token && !all_digits(token) && ec)
		{
			local_ec = input_err;
		}
		if (sscanf(token, "%d", &value) != 1)
		{
			local_ec = input_err;
		}
		out[*size] = value;
		*size += 1;
		if (*size > max_size)
			local_ec = input_array_overflow_err;
		token = strtok(NULL, " ");
	}
	if (ec)
		*ec = local_ec;
}

int read_int(int *ec)
{
	char buffer[BUFFER_SIZE];
	char temp[BUFFER_SIZE];
	int target = 0;
	int temp_int = 0;
	fgets(buffer, BUFFER_SIZE, stdin);
	if (sscanf(buffer, "%d", &target) != 1)
		*ec = input_err;
	if (sscanf(buffer, "%d %s", &temp_int, temp) == 2)
		*ec = input_err;
	if (strcmp(buffer, "\n") == 0)
		fgets(buffer, BUFFER_SIZE, stdin);
	return target;
}

