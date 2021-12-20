#include "list.h"
#include <stdlib.h>
#include <string.h>

struct node *node_new(void *value, int el_size)
{
	struct node *self = malloc(sizeof(struct node) + el_size);
	self->value = (char* )self + sizeof(struct node);
	memcpy(self->value, value, el_size);
	return self;
}

void node_delete(struct node *self)
{
	free(self);
}

void node_get(struct node *self, void *value, int size)
{
	memcpy(value, self->value, size);
}

struct list list_new(int el_size)
{
	struct list self = {.el_size = el_size };
	return self;
}

void list_head(struct list *self, void *value)
{
	node_get(self->head, value, self->el_size);
}

int list_next(struct list *self)
{
	if (self->head != NULL)
		self->head = self->head->next;
	return self->head != NULL;
}

void list_delete(struct list *self)
{
	struct node *cur = self->head;
	while (cur)
	{
		struct node *next = cur->next;
		if (self->item_destructor != NULL)
			self->item_destructor(cur->value);
		node_delete(cur);
		cur = next;
	}
}

void list_add(struct list *self, void *value)
{
	struct node *to_add = node_new(value, self->el_size);
	if (self->head == NULL)
		self->head = to_add;
	if (self->tail != NULL)
		self->tail->next = to_add;
	self->tail = to_add;
}
