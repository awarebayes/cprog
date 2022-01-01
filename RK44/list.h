#ifndef __LIST_H__
#define __LIST_H__

struct node
{
	struct node *next;	
	void *value;
};


struct list
{
	struct node *head;
	struct node *tail;
	int el_size;
	void (*item_destructor)(void *self);
};

struct node *node_new(void *value, int el_size);
void node_delete(struct node *self);
void node_get(struct node *self, void *value, int size);
struct list list_new(int el_size); // constructor
void list_delete(struct list *self); // destructor
void list_head(struct list *self, void *value);
void list_add(struct list *self, void *value);
int list_next(struct list *self);

#endif
