//
// Created by dev on 11/14/21.
//

#include <assert.h>
#include "term.h"
#include "util.h"

int powi(int base, int pow)
{
	int result = 1;
	int flag = 1;
	while (flag)
	{
		if (pow & 1)
			result *= base;
		pow >>= 1;
		if (!pow)
			flag = 0;
		else
			base *= base;
	}

	return result;
}

int term_eval(term_t *self, int x)
{
	return self->coef * powi(x, self->pow);
}

term_t term_derivative(term_t *self)
{
	term_t result = { .pow = self->pow, .coef = self->coef };
	result.coef *= result.pow;
	result.pow -= 1;
	if (result.pow == -1)
	{
		result.pow = 0;
		result.coef = 0;
	}
	return result;
}

int term_zero(term_t *self)
{
	return self->pow == 0 && self->coef == 0;
}

term_t term_sum(term_t *self, term_t *other)
{
	assert(self->pow == other->pow);
	term_t result = { 0 };
	result.coef = self->coef + other->coef;
	result.pow = self->pow;
	return result;
}
