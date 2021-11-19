//
// Created by dev on 11/16/21.
//
#include "cli.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n_applicants = 0;
	int ec = 0;
	enrollment_t enrolled = { 0 };
	applicant_t *applicant_storage = NULL;
	node_t *applicants = NULL;
	n_applicants = read_int(&ec);
	if (!ec)
		applicant_storage = malloc(n_applicants * sizeof(applicant_t));
	if (!ec)
		applicants = get_applicants(n_applicants, applicant_storage, &ec);
	if (!ec)
		enrolled = accept_applicants(applicants, &ec);
	if (!ec)
	{
		printf("---------------------\n");
		applicant_print(enrolled.grotter);
		applicant_print(enrolled.best_gpa);
		for (int i = 0; i < enrolled.n_others; i++)
			applicant_print(&enrolled.others[i]);
	}
	free(applicant_storage);
	return ec;
}
