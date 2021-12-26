//
// Created by dev on 11/16/21.
//

#ifndef LAB_10_01_01_APPLICANT_C
#define LAB_10_01_01_APPLICANT_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "applicant.h"
#include "cli.h"
#include "util.h"
#include "../inc/applicant.h"

#define BUF_SIZE 1024

applicant_t applicant_new(char *name, float gpa)
{
	applicant_t self = { 0 };
	strncpy(self.name, name, MAXNAME);
	name[MAXNAME - 1] = '\0';
	self.gpa = gpa;
	return self;
}

applicant_t applicant_read(int *ec)
{
	char name[BUF_SIZE];
	float gpa = 0;
	fgets(name, BUF_SIZE, stdin);
	name[strcspn(name, "\r\n")] = 0;
	if (!*name)
		*ec = input_err;
	gpa = read_float(ec);

	return applicant_new(name, gpa);
}

void applicant_print(applicant_t *self)
{
	printf("%s\n%f\n", self->name, self->gpa);
}

#endif //LAB_10_01_01_APPLICANT_C
