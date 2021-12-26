//
// Created by dev on 11/14/21.
//

#ifndef LAB_10_02_21_TERM_H
#define LAB_10_02_21_TERM_H

typedef struct
{
	int coef;
	int pow;
} term_t;

int term_eval(term_t *self, int x);

term_t term_derivative(term_t *self);

int term_zero(term_t *self);

term_t term_sum(term_t *self, term_t *other);

#endif //LAB_10_02_21_TERM_H
