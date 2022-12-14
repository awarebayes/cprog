#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "my_printf.h"

static int number_len(unsigned int num, int base)
{
	if (num == 0)
		return 1;

	int len = 0;
	while (num != 0)
	{
		num /= base;
		len += 1;
	}
	return len;
}

int powi(int x, unsigned n)
{
	int p = x;
	int r = 1;

	while (n > 0)
	{
		if (n % 2 == 1)
			r *= p;
		p *= p;
		n /= 2;
	}

	return r;
}

static int print_int(char *restrict s, int n, int num, int base)
{
	char digits[] = "0123456789";
	int n_printed_theoretic = 0;

	if (num < 0 && base == 10)
	{
		if (n_printed_theoretic < n)
		{
			(*s++) = '-';
		}
		num = -num;
		n_printed_theoretic++;
	}
	else if (num < 0 && base != 10)
		num = (UINT_MAX + 1) + (unsigned) num;

	unsigned unum = (unsigned) num;

	int len = number_len(unum, base);
	int powered = powi(base, len - 1);

	while (powered != 0)
	{
		if (n_printed_theoretic < n)
			(*s++) = digits[unum / powered];

		unum = unum % powered;
		powered /= base;

		n_printed_theoretic++;
	}

	return n_printed_theoretic;
}


static int print_string(char *restrict s, int n, char *restrict source)
{
	int n_printed = 0;
	int n_printed_theoretic = 0;

	while (source && *source)
	{
		if (n_printed < n)
		{
			*(s++) = *(source++);
			n_printed++;
		}
		else
			source++;
		n_printed_theoretic++;
	}
	return n_printed_theoretic;
}


int my_snprintf(char *restrict s, int n, const char *restrict fmt, ...)
{
	if (s != NULL)
		memset(s, 0, n);
	if (n < 0 || fmt == NULL)
		return -1;
	va_list ap;
	va_start(ap, fmt);

	int temp_int;
	char temp_char;
	char *temp_str = NULL;
	char *s_started = s;

	int printed_theoretic = 0;
	int sub_printed = 0;
	int format_started = 0;
	int can_write = 0;
	int can_write_single = 1;
	int left_to_write = 0;
	int ec = 0;

	while (fmt && *fmt && !ec)
	{
		can_write = (s < s_started + n) && (s_started != NULL);
		left_to_write = n - printed_theoretic - 1;
		can_write_single = can_write && (left_to_write > 0) && (s_started != NULL);

		if (*fmt == '%')
		{
			format_started = 1;
			fmt++;
		}

		if (format_started)
		{
			switch (*fmt)
			{
				case 'd':
				case 'i':
					temp_int = va_arg(ap, int);
					sub_printed = print_int(s, left_to_write, temp_int, 10);
					break;
				case 'o':
					temp_int = va_arg(ap, int);
					sub_printed = print_int(s, left_to_write, temp_int, 8);
					break;
				case '%':
					if (can_write_single)
						*s = '%';
					sub_printed = 1;
					break;
				case 'c':
					temp_char = (char) va_arg(ap, int);
					if (can_write_single)
						*s = temp_char;
					sub_printed = 1;
					break;
				case 's':
					temp_str = va_arg(ap, char *);
					sub_printed = print_string(s, left_to_write, temp_str);
					break;
				default:
					ec = 1;
					break;
			}
		}
		else
		{
			if (can_write_single)
				*s = *fmt;
			sub_printed = 1;
		}
		fmt++;
		format_started = 0;
		printed_theoretic += sub_printed;
		s += sub_printed;
		sub_printed = 0;
	}
	if (can_write_single)
		(*s) = '\0';
	else if (s_started != NULL)
		s_started[n - 1] = '\0';

	int res = printed_theoretic;
	if (ec)
		res = -1;
	return res;
}