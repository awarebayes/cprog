//
// Created by dev on 11/15/21.
//
#include "cli.h"
#include "poly.h"
#include "util.h"
#include <stdio.h>

#define BUF_SIZE 1024

poly_t read_poly(int *ec)
{
	char buf[BUF_SIZE];
	fgets(buf, BUF_SIZE, stdin);
	poly_t poly = poly_from_string(buf, ec);
	return poly;
}

void val(int *ec)
{
	int x = 0;
	int result = 0;
	poly_t poly = read_poly(ec);
	if (!*ec)
		x = read_int(ec);
	if (!*ec)
	{
		result = poly_eval(&poly, x, ec); // todo is 0 0 bad for eval?
		printf("<out\n%d\n", result);
	}
	poly_delete(&poly);
}

void ddx(int *ec)
{
	poly_t poly = read_poly(ec);
	poly_t result = { 0 };
	if (!*ec)
	{
		result = poly_derivative(&poly, ec); // todo is 0 0 bad for eval?
		printf("<out\n");
		poly_print(&result);
	}
	poly_delete(&poly);
	poly_delete(&result);
}

void sum(int *ec)
{
	poly_t poly1 = { 0 };
	poly_t poly2 = { 0 };
	poly_t result = { 0 };
	poly1 = read_poly(ec);
	if (!*ec)
		poly2 = read_poly(ec);
	if (!*ec)
	{
		result = poly_sum(&poly1, &poly2, ec); // todo is 0 0 bad for eval?
		printf("<out\n");
		poly_print(&result);
	}
	poly_delete(&poly1);
	poly_delete(&poly2);
	poly_delete(&result);
}

void dvd(int *ec)
{

	poly_t poly = read_poly(ec);
	poly_t even = { 0 };
	poly_t odd = { 0 };
	if (!*ec)
	{
		poly_split_odd_even_power(&poly, &odd, &even, ec); // todo is 0 0 bad for eval?
		printf("<out\n");
		poly_print(&even);
		poly_print(&odd);
	}
	poly_delete(&poly);
	poly_delete(&even);
	poly_delete(&odd);
}