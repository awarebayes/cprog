//
// Created by dev on 11/10/21.
//


#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "memory.h"
#include "util.h"

node_t *node_new(int coef, int pow, int *ec)
{
	node_t *self = (node_t *) malloc(sizeof(node_t));
	if (self == NULL && ec)
		*ec = bad_malloc_err;
	else
	{
		self->term.coef = coef;
		self->term.pow = pow;
		self->next = NULL;
	}
	return self;
}

void node_delete(node_t *self)
{
	free(self);
}


