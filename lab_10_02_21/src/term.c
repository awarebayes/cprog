//
// Created by dev on 11/14/21.
//

#include "term.h"
#include "math.h"

int term_apply(term_t *self, int x)
{
	return self->coef * powi(x, self->pow);
}