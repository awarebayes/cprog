//
// Created by dev on 11/22/21.
//
#include <stdio.h>
#include <limits.h>
#include "my_printf.h"

int main()
{
	int buf_size = 30;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 123);
	int printed_my = my_snprintf(buf, buf_size, fmt, 123);
	return 0;
}