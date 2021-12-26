//
// Created by dev on 11/14/21.
//

#ifndef LAB_10_02_21_POLY_H
#define LAB_10_02_21_POLY_H

#include "node.h"

typedef struct
{
	node_t *first;
	node_t *last;
} poly_t;

poly_t poly_from_array(int *arr, int n, int *ec);

poly_t poly_from_string(char *string, int *ec);

void poly_add(poly_t *self, int coef, int pow, int *ec);

void poly_add_term(poly_t *self, term_t *term, int *ec);

int poly_eval(poly_t *self, int x, int *ec);

void poly_delete(poly_t *self);

int poly_equal(poly_t *self, poly_t *other);

poly_t poly_derivative(poly_t *self, int *ec);

poly_t poly_sum(poly_t *self, poly_t *other, int *ec);

void poly_split_odd_even_power(poly_t *self, poly_t *odd, poly_t *even, int *ec);

int poly_is_null(poly_t *self);

void poly_print(poly_t *self);

#endif //LAB_10_02_21_POLY_H
