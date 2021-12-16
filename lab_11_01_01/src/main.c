//
// Created by dev on 11/22/21.
//
#include <stdio.h>
#include <limits.h>
#include "my_printf.h"

int main()
{

	int buf_size = 10;
	char *buf = NULL;
	char *target_buf = NULL;
	char *fmt = "aboba";

	// int printed_target = snprintf(NULL, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	return 0;
}