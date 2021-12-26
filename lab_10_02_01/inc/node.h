//
// Created by dev on 11/11/21.
//

#ifndef IU7_CPROG_LABS_2021_SCHERBINAMIKHAIL_LIST_H
#define IU7_CPROG_LABS_2021_SCHERBINAMIKHAIL_LIST_H

#include <stdio.h>
#include "term.h"

struct node_t;
typedef struct node_t node_t;

struct node_t
{
	term_t term;
	struct node_t *next;
};

node_t *node_new(int coef, int pow, int *ec);

node_t *node_from_term(term_t *term, int *ec);

void list_delete(node_t *head);

void node_delete(node_t *self);

void *pop_front(node_t **head);


#endif //IU7_CPROG_LABS_2021_SCHERBINAMIKHAIL_LIST_H
