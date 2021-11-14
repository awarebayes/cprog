//
// Created by dev on 11/11/21.
//

#ifndef IU7_CPROG_LABS_2021_SCHERBINAMIKHAIL_LIST_H
#define IU7_CPROG_LABS_2021_SCHERBINAMIKHAIL_LIST_H

#include <stdio.h>

struct node_t;
typedef struct node_t node_t;

struct node_t
{
	void *data;
	struct node_t *next;
};

typedef int (*comparator_t)(const void *a, const void *b);

node_t *node_new(void *value, int *ec);

void list_delete(node_t *head);

void node_delete(node_t *self);

node_t *find(node_t *head, const void *data, comparator_t comparator);

void *pop_front(node_t **head);

int copy(node_t *head, node_t **new_head_ptr);

void sorted_insert(node_t **head, node_t *element, comparator_t comparator);

node_t *sort(node_t *head, comparator_t comparator);

void print_as_int(node_t *head);

#endif //IU7_CPROG_LABS_2021_SCHERBINAMIKHAIL_LIST_H
