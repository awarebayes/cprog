//
// Created by dev on 11/19/21.
//
#include "util.h"
#include "cli.h"
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 1024

int read_int(int *ec)
{
	char buffer[BUF_SIZE];
	char temp[BUF_SIZE];
	int target = 0;
	int temp_int = 0;
	fgets(buffer, BUF_SIZE, stdin);
	if (sscanf(buffer, "%d", &target) != 1)
		*ec = input_err;
	if (sscanf(buffer, "%d %s", &temp_int, temp) == 2)
		*ec = input_err;
	return target;
}

float read_float(int *ec)
{
	char buffer[BUF_SIZE];
	char temp[BUF_SIZE];
	float target = 0;
	float temp_float = 0;
	fgets(buffer, BUF_SIZE, stdin);
	if (sscanf(buffer, "%f", &target) != 1)
		*ec = input_err;
	if (sscanf(buffer, "%f %s", &temp_float, temp) == 2)
		*ec = input_err;
	return target;
}
