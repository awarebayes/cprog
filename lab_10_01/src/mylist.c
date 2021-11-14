//
// Created by dev on 11/10/21.
//


#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"
#include "memory.h"

#define bad_malloc 1
#define copied_error 2
#define nullptr_err 3

node_t *node_new(void *value, int *ec)
{
	node_t *self = (node_t *) malloc(sizeof(node_t));
	if (self == NULL && ec)
	{
		*ec = bad_malloc;
	}
	else
	{

		self->data = value;
		self->next = NULL;
	}
	return self;
}

void node_delete(node_t *self)
{
	free(self);
}

void list_delete(node_t *head)
{
	while (head)
	{
		node_t *current = head;
		head = head->next;
		free(current);
	}
}

node_t *find(node_t *head, const void *data, comparator_t comparator)
{
	node_t *result = NULL;
	int flag = 1;
	while (head != NULL)
	{
		if (comparator(head->data, data) == 0 && flag)
		{
			result = head;
			flag = 0;
		}
		else
		{
			head = head->next;
		}
	}
	return result;
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

int copy(node_t *head, node_t **new_head_ptr)
{
	if (!head)
		return nullptr_err;

	int ec = 0;
	node_t *new_head = node_new(head, &ec);
	node_t *node_dst = new_head;
	node_t *node_src = head;
	while (node_src && !ec)
	{
		node_dst->data = head->data;
		head = head->next;
		if (head != NULL)
			node_dst->next = node_new(0, &ec);
		node_dst = node_dst->next;
		node_src = node_src->next;
	}
	if (!ec)
		(*new_head_ptr) = new_head;
	else
		(*new_head_ptr) = NULL;
	return ec;
}

void sorted_insert(node_t **head, node_t *element, comparator_t comparator)
{

	node_t *curr = *head;
	node_t *prev = NULL;
	if (curr == NULL)
		*head = element;
	else
	{
		while (curr && comparator(curr->data, element->data) < 0)
		{
			prev = curr;
			curr = curr->next;
		}
		if (prev)
			prev->next = element;
		else
			*head = element;
		element->next = curr;
	}
}

node_t *sort(node_t *head, comparator_t comparator)
{
	node_t *new = NULL;
	while (head)
	{
		void *value = pop_front(&head);
		node_t *new_node = node_new(value, NULL);
		sorted_insert(&new, new_node, comparator);
	}
	return new;
}

void print_as_int(node_t *head)
{
	while (head)
	{
		printf("%d -> ", *((int *) head->data));
		head = head->next;
	}
	printf("null\n");
}
