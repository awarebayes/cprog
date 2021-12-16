//
// Created by dev on 11/22/21.
//
#include <stdio.h>
#include <limits.h>
#include "my_printf.h"

int main()
{

	int buf_size = 5;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = NULL;

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);
	return 0;
}