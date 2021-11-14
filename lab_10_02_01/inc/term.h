//
// Created by dev on 11/14/21.
//

#ifndef LAB_10_02_21_TERM_H
#define LAB_10_02_21_TERM_H

typedef struct
{
	int pow;
	int coef;
} term_t;

int term_apply(term_t *self, int x);

#endif //LAB_10_02_21_TERM_H
