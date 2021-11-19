//
// Created by dev on 11/16/21.
//

#include "mylist.h"
#include "cli.h"
#include "applicant.h"
#include <string.h>

#define DELTA 0.001

static int is_grotter(applicant_t *app)
{
	return strstr(app->name, "Grotter") != NULL;
}

static int applicant_cmp_gpa(const void *a, const void *b)
{
	applicant_t *a_app = (applicant_t *) a;
	applicant_t *b_app = (applicant_t *) b;
	float gpa_diff = a_app->gpa - b_app->gpa;
	int result = 0;
	if (gpa_diff > DELTA)
		result = 1;
	else if (gpa_diff < -DELTA)
		result = -1;
	return -result;
}

static applicant_t *node_to_applicant(node_t *node)
{
	return (applicant_t *) node->data;
}

node_t *get_applicants(int n, void *memory, int *ec)
{
	int read = 0;
	node_t *first = NULL;
	node_t *last = NULL;
	char *memory_ptr = memory;
	while (read < n && !*ec)
	{
		applicant_t new = applicant_read(ec);
		read += 1;
		memcpy(memory_ptr, &new, sizeof(applicant_t));
		node_t *node = node_new(memory_ptr, ec);
		memory_ptr += sizeof(applicant_t);
		if (last == NULL)
		{
			first = node;
			last = node;
		}
		else
		{
			last->next = node;
			last = node;
		}
	}
	return first;
}


enrollment_t accept_applicants(node_t *list, int *ec)
{
	enrollment_t result = { 0 };
	node_t *sorted = sort(list, applicant_cmp_gpa);

	while (node_to_applicant(sorted)->gpa > 5)
		pop_front(&sorted);

	int accepted = 0;
	while (sorted != NULL && !*ec)
	{
		applicant_t *applicant = pop_front(&sorted);
		if (is_grotter(applicant))
			result.grotter = applicant;
		else if (accepted == 0 && result.best_gpa == NULL)
			result.best_gpa = applicant;
		else if (accepted < 5)
		{
			result.others[accepted] = *applicant;
			accepted += 1;
		}
	}
	result.n_others = accepted;

	return result;
}
