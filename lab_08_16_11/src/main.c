#include <stdio.h>
#include <string.h>
#include "util.h"
#include "matrix.h"

int main(int argc, char **argv)
{
	FILE *mf1 = NULL, *mf2 = NULL, *mfout = NULL;
	matrix_t m1 = { 0 }, m2 = { 0 }, res = { 0 };
	double dres = 0.0;
	int ec = ok;
	if (argc != 5 && argc != 4)
		ec = arg_err;
	if (!ec)
	{
		if (strcmp(argv[1], "a") == 0)
		{
			if (argc != 5)
				ec = arg_err;
			if (!ec)
			{
				mf1 = fopen(argv[2], "r");
				mf2 = fopen(argv[3], "r");
			}
			if (mf1 == NULL || mf2 == NULL)
				ec = file_err;
			if (!ec)
				m1 = matrix_from_file(mf1, &ec);
			if (!ec)
				m2 = matrix_from_file(mf2, &ec);
			if (!ec)
				res = matrix_add(&m1, &m2, &ec);
			if (!ec)
			{
				mfout = fopen(argv[4], "w");
				if (mfout == NULL)
					ec = file_err;
			}
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
			}
			if (mf1 == NULL || mf2 == NULL)
				ec = file_err;
			if (!ec)
				m1 = matrix_from_file(mf1, &ec);
			if (!ec)
				m2 = matrix_from_file(mf2, &ec);
			if (!ec)
				res = matrix_mul(&m1, &m2, &ec);
			if (!ec)
			{
				mfout = fopen(argv[4], "w");
				if (mfout == NULL)
					ec = file_err;
			}
			if (!ec)
				matrix_print(&res, mfout);
		}

		else if (strcmp(argv[1], "c") == 0)
		{
			if (argc != 4)
				ec = arg_err;
			if (!ec)
				mf1 = fopen(argv[2], "r");
			if (mf1 == NULL)
				ec = file_err;
			if (!ec)
				m1 = matrix_from_file(mf1, &ec);
			if (!ec)
				dres = matrix_determinant(&m1, &ec);
			if (!ec)
			{
				mfout = fopen(argv[3], "w");
				if (mfout == NULL)
					ec = file_err;
			}
			if (!ec)
				fprintf(mfout,"%.6lf", dres);
		}
		else
			ec = arg_err;
	}
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
