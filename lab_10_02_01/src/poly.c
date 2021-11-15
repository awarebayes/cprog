//
// Created by dev on 11/14/21.
//

#include "poly.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>

#define TEMP_BUF_SIZE 1000

// @destructor
void poly_delete(poly_t *self)
{
	node_t *head = self->first;
	while (head)
	{
		node_t *current = head;
		head = head->next;
		free(current);
	}
}

int poly_eval(poly_t *self, int x, int *ec)
{
	int local_ec = ok;
	int sum = 0;
	if (self == NULL || self->first == NULL)
		local_ec = bad_eval_err;
	node_t *node = self->first;
	while (node)
	{
		sum += term_eval(&node->term, x);
		node = node->next;
	}
	if (ec)
		*ec = local_ec;
	return sum;
}

// TODO delete
void print(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

static void check_power(node_t *self, node_t *last, int *ec)
{
	if (self->term.pow >= last->term.pow)
		*ec = input_err;
}

void poly_add(poly_t *self, int coef, int pow, int *ec)
{
	int local_ec = ok;
	node_t *new = node_new(coef, pow, &local_ec);
	if (self->last != NULL)
	{
		check_power(new, self->last, &local_ec);
		self->last->next = new;
		self->last = new;
	}
	else
	{
		self->last = new;
		self->first = new;
	}
	if (ec)
		*ec = local_ec;
}

void poly_add_term(poly_t *self, term_t *term, int *ec)
{
	// todo remove
	//if (!term_zero(term))
	poly_add(self, term->coef, term->pow, ec);
	//else if (ec)
	//	*ec = zero_term_added_err;
}

// @constructor
poly_t poly_from_array(int *arr, int n, int *ec)
{
	poly_t self = { 0 };
	if (n % 2 != 0 || n == 0)
		return self;

	int local_ec = ok;
	for (int i = 0; i < n && !local_ec;)
	{
		poly_add(&self, arr[i], arr[i + 1], &local_ec);
		i += 2;
	}
	if (ec)
		*ec = local_ec;
	return self;
}


// @constructor
poly_t poly_from_string(char *string, int *ec)
{
	int *buf = malloc(sizeof(int) * TEMP_BUF_SIZE);
	int n_integers = 0;
	int local_ec = ok;
	poly_t self = { 0 };
	read_int_array(buf, &n_integers, TEMP_BUF_SIZE, string, &local_ec);
	if (n_integers % 2 != 0)
		local_ec = input_err;
	if (!local_ec)
		self = poly_from_array(buf, n_integers, &local_ec);
	if (ec)
		*ec = local_ec;
	free(buf);
	return self;
}

poly_t poly_derivative(poly_t *self, int *ec)
{
	poly_t result = { 0 };
	node_t *node = self->first;
	int local_ec = ok;
	while (node && !term_zero(&node->term) && !local_ec)
	{
		term_t dterm_dx = term_derivative(&node->term);
		if (!term_zero(&dterm_dx))
		{
			poly_add_term(&result, &dterm_dx, &local_ec);
		}
		node = node->next;
	}
	// TODO: consider handler for null_poly_err
	if (ec)
		*ec = local_ec;
	return result;
}

int poly_equal(poly_t *self, poly_t *other)
{
	node_t *node_1 = self->first;
	node_t *node_2 = other->first;
	int flag = 1;

	while (node_1 && node_2 && flag)
	{
		if (node_1->term.pow != node_2->term.pow)
			flag = 0;
		if (node_1->term.coef != node_2->term.coef)
			flag = 0;
		node_1 = node_1->next;
		node_2 = node_2->next;
	}
	if (node_1 != NULL || node_2 != NULL)
		flag = 0;
	return flag;
}

poly_t poly_sum(poly_t *self, poly_t *other, int *ec)
{
	node_t *node_1 = self->first;
	node_t *node_2 = other->first;
	poly_t result = { 0 };
	int local_ec = ok;

	while (node_1 || node_2)
	{
		if (node_1 != NULL && (node_2 == NULL || node_1->term.pow > node_2->term.pow))
		{
			poly_add_term(&result, &node_1->term, ec);
			node_1 = node_1->next;
		}
		else if (node_1 == NULL || node_1->term.pow < node_2->term.pow)
		{
			poly_add_term(&result, &node_2->term, ec);
			node_2 = node_2->next;
		}
		else if (node_1->term.pow == node_2->term.pow)
		{
			term_t sum = term_sum(&node_1->term, &node_2->term);
			poly_add_term(&result, &sum, ec);
			node_1 = node_1->next;
			node_2 = node_2->next;
		}
	}

	if (ec)
		*ec = local_ec;
	return result;
}

void poly_split_odd_even_power(poly_t *self, poly_t *odd, poly_t *even, int *ec)
{
	assert(even != NULL && odd != NULL);
	node_t *node = self->first;
	int local_ec = ok;
	while (node && !local_ec)
	{
		if (node->term.pow % 2 == 0)
			poly_add_term(even, &node->term, &local_ec);
		else
			poly_add_term(odd, &node->term, &local_ec);
		node = node->next;
	}
	if (ec)
		*ec = local_ec;
}

int poly_is_null(poly_t *self)
{
	int has_null_ptr = (self->first == self->last && self->first == NULL);
	int is_zero = (self->first != 0 && term_zero(&self->first->term));
	return has_null_ptr || is_zero;
}

void poly_print(poly_t *self)
{
	node_t *node = self->first;

	while (node != NULL)
	{
		printf("%d %d ", node->term.coef, node->term.pow);
		node = node->next;
	}
	printf("L");
}