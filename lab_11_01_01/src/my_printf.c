#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include "my_printf.h"

#define INT_BUF 16
#define UINT_MAX_HEX

static void str_reverse(char *s, int n)
{
	char temp_char;
	for (int i = 0; i < n / 2; i++)
	{
		temp_char = s[n - i - 1];
		s[n - i - 1] = s[i];
		s[i] = temp_char;
	}
}

int int_to_oct(int decimalnum)
{
	int octalnum = 0, temp = 1;

	while (decimalnum != 0)
	{
		octalnum = octalnum + (decimalnum % 8) * temp;
		decimalnum = decimalnum / 8;
		temp = temp * 10;
	}

	return octalnum;
}


static int print_int(char *restrict s, int n, int num)
{
	char buf[INT_BUF] = { 0 };
	char *buf_ptr = buf;
	int n_printed = 0;
	int n_printed_theoretic = 0;
	int neg_flag = 0;

	long long lnum = num;


	if (lnum == 0)
	{
		*(buf_ptr++) = '0';
		n_printed_theoretic++;
	}
	else
	{
		if (lnum < 0)
		{
			n_printed_theoretic++;
			neg_flag = 1;
			lnum *= -1;
		}
		while (lnum != 0)
		{
			int digit = (int)(lnum % 10);
			(*buf_ptr++) = digit + '0';
			if (n_printed < n)
				n_printed++;
			n_printed_theoretic++;
			lnum /= 10;
		}
		if (neg_flag)
			*(buf_ptr++) = '-';
		str_reverse(buf, (int) n_printed_theoretic);
	}
	strncpy(s, buf, n_printed_theoretic);
	return (int) n_printed_theoretic;
}


static int print_unsigned_int_as_octal(char *restrict s, int n, int unsigned num)
{
	char buf[INT_BUF] = { 0 };
	char *buf_ptr = buf;
	int n_printed = 0;
	int n_printed_theoretic = 0;
	int neg_flag = 0;

	if (num == 0)
	{
		*(buf_ptr++) = '0';
		n_printed_theoretic++;
	}
	else
	{
		while (num != 0)
		{
			int digit = (int)(num % 8);
			(*buf_ptr++) = digit + '0';
			if (n_printed < n)
				n_printed++;
			n_printed_theoretic++;
			num /= 8;
		}
		if (neg_flag)
			*(buf_ptr++) = '-';
		str_reverse(buf, (int) n_printed_theoretic);
	}
	strncpy(s, buf, n_printed_theoretic);
	return (int) n_printed_theoretic;
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
	return (int) n_printed_theoretic;
}



int my_snprintf(char *restrict s, size_t n, const char *restrict fmt, ...)
{
	memset(s, 0, n);
	va_list ap;
	va_start(ap, fmt);

	int temp_int = -123;
	unsigned int temp_uint = 0;
	char temp_char = '*';
	char *temp_str = NULL;
	char *s_started = s;

	int printed_theoretic = 0;
	int sub_printed = 0;
	int format_started = 0;
	int can_write = 0;
	int ec = 0;

	while (fmt && *fmt && !ec)
	{
		can_write = s < s_started + n;

		if (*fmt == '%')
		{
			format_started = 1;
			fmt++;
		}


		if (format_started)
		{
			switch (*fmt)
			{
				case 'd': // integer
				case 'i': // also integer
					temp_int = va_arg(ap,
					                  int);
					sub_printed = print_int(s, (int) n - printed_theoretic - 1, temp_int);
					break;
				case 'o': // also integer
					temp_uint = va_arg(ap, unsigned int);
					sub_printed = print_unsigned_int_as_octal(s, (int)n - printed_theoretic - 1, temp_uint);
					break;
				case '%':
					if (can_write)
						*s = '%';
					sub_printed = 1;
					break;
				case 'c': // char
					temp_char = (char) va_arg(ap, int);
					if (can_write)
						*s = temp_char;
					sub_printed = 1;
					break;
				case 's': // string
					temp_str = va_arg(ap, char *);
					sub_printed = print_string(s, (int) n - printed_theoretic - 1, temp_str);
					break;
				default:
					ec = 1;
					break;
			}
		}
		else
		{
			if (can_write)
				*s = *fmt;
			sub_printed = 1;
		}
		fmt++;
		format_started = 0;
		printed_theoretic += sub_printed;
		s += sub_printed;
		sub_printed = 0;
	}
	if (can_write)
		(*s) = '\0';
	else
		s_started[n-1] = '\0';

	return printed_theoretic;
}