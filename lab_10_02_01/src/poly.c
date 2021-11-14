//
// Created by dev on 11/14/21.
//

#include "poly.h"


void poly_delete(poly_t *self)
{
	node_t *node = self->first;
	while (head)
	{
		node_t *current = head;
		head = head->next;
		free(current);
	}
}

void *pop_front(node_t **head)
{
	if (*head == NULL)
		return NULL;
	void *result = (*head)->data;
	node_t *current_ptr = *head;
	(*head) = (*head)->next;
	free(current_ptr);
	return result;
}
