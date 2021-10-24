#include <stdio.h>
#include <string.h>
#include "util.h"
#include "matrix.h"

int main(int argc, char **argv)
{
	FILE *mf1 = NULL, *mf2 = NULL, *mfout = NULL;
	matrix_t m1 = { 0 }, m2 = { 0 }, res = { 0 };
	int ec = ok;
	if (argc != 5 && argc != 4)
		return arg_err;

	if (strcmp(argv[1], "a") == 0)
	{
		if (argc != 5)
			ec = arg_err;
		if (!ec)
		{
			mf1 = fopen(argv[2], "r");
			mf2 = fopen(argv[3], "r");
			mfout = fopen(argv[4], "w");
		}
		if (mf1 == NULL || mf2 == NULL || mfout == NULL)
			ec = file_err;
		if (!ec)
			m1 = matrix_from_file(mf1, &ec);
		if (!ec)
			m2 = matrix_from_file(mf2, &ec);
		if (!ec)
			res = matrix_add(&m1, &m2, &ec);
		if (!ec)
			matrix_print(&res, mfout);
	}
	else if (strcmp(argv[1], "m") == 0)
	{
		if (argc != 5)
			ec = arg_err;
		if (!ec)
		{
			mf1 = fopen(argv[2], "r");
			mf2 = fopen(argv[3], "r");
			mfout = fopen(argv[4], "w");
		}
		if (mf1 == NULL || mf2 == NULL || mfout == NULL)
			ec = file_err;
		if (!ec)
			m1 = matrix_from_file(mf1, &ec);
		if (!ec)
			m2 = matrix_from_file(mf2, &ec);
		if (!ec)
			res = matrix_mul(&m1, &m2, &ec);
		if (!ec)
			matrix_print(&res, mfout);
	}
	else if (strcmp(argv[1], "o") == 0)
	{
		if (argc != 4)
			ec = arg_err;
		if (!ec)
		{
			mf1 = fopen(argv[2], "r");
			mfout = fopen(argv[3], "w");
		}
		if (mf1 == NULL || mfout == NULL)
			ec = file_err;
		if (!ec)
			m1 = matrix_from_file(mf1, &ec);
		if (!ec)
			res = gaussian_solve(&m1, &ec);
		if (!ec)
			matrix_print(&res, mfout);
	}
	else
		ec = arg_err;
	
	if (mf1)
		fclose(mf1);
	if (mf2)
		fclose(mf2);
	if (mfout)
		fclose(mfout);
	matrix_delete(&m1);
	matrix_delete(&m2);
	matrix_delete(&res);
	return ec;
}
