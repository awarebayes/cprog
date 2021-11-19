//
// Created by dev on 11/16/21.
//

#ifndef LAB_10_01_01_CLI_H
#define LAB_10_01_01_CLI_H

#include "applicant.h"
#include "mylist.h"

typedef struct
{
	applicant_t *grotter;
	applicant_t *best_gpa;
	applicant_t others[5];
	int n_others;
} enrollment_t;

enum error_u
{
	ok,
	input_err,
};


node_t *get_applicants(int n, void *memory, int *ec);

enrollment_t accept_applicants(node_t *list, int *ec);

#endif //LAB_10_01_01_CLI_H
