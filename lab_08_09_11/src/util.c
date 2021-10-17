#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *read_arr(FILE *fin, int n, int *ec)
{
    if (fin == NULL)
        *ec = file_err;
    double *temp_buf = (double*)malloc(n * sizeof(double));
    int n_scanned = 0;
    for (int i = 0; i < n; i++)
    {
        if (fscanf(fin, "%lf", temp_buf + i) != 1)
			*ec = input_err;
		else
			n_scanned++;
    }
    if (n_scanned != n)
        *ec = input_err;
    return temp_buf;
}


int fcmp(double f1, double f2)
{
	if (fabs(fabs(f1)-fabs(f2)) < PREC)
		return 0;
	if (f1 > f2)
		return 1;
	else
		return -1;
}
