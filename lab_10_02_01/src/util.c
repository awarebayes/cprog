//
// Created by dev on 11/14/21.
//
#include "string.h"
#include "util.h"

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

void read_int_array(int *out, int *size, char *in, int *ec)
{
	int local_ec = ok;
	token = strtok(in, " ");
	int value = 0;
	*size = 0;
	while (token && local_ec)
	{
		remove_lc(token);
		if (*token && !all_digits(token) && ec)
		{
			local_ec = input_error;
		}
		if (sscanf(token, "%d", &value) != 1)
		{
			local_ec = input_error;
		}
		out[*size] = value;
		size += 1;
		token = strtok(NULL, " ");
	}
	if (ec)
		*ec = local_ec;
}
