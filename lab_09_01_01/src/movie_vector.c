#include "movie_vector.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>

vector_t vector_new(int capacity)
{
	vector_t self = { 0 };
	self.size = 0;
	self.capacity = capacity;
	self.pointer = calloc(capacity, sizeof(movie_t));
	return self;
}

void vector_delete(vector_t *self)
{
	for (int i = 0; i < self->size; i++)
	{
		movie_delete(self->pointer + i);
	}
	free(self->pointer);
	self->pointer = NULL;
}

vector_t vector_realloc(vector_t *self)
{
	vector_t new_vec = vector_new(self->capacity * 2);
	new_vec.size = self->size;
	for (int i = 0; i < self->size; i++)
		new_vec.pointer[i] = self->pointer[i];
	// vector_delete(self);
	free(self->pointer);
	*self = new_vec;
	return new_vec;
}

movie_t *vector_get(vector_t *self, int index)
{
	return self->pointer + index;
}

// shifts right from pos
void vector_shift_right(vector_t *self, int from)
{
	for (int i = self->size; i > from; i--)
		self->pointer[i] = self->pointer[i - 1];
}

void vector_insert(vector_t *self, movie_t *m, int pos)
{
	if (self->size + 1 >= self->capacity)
		*self = vector_realloc(self);
	vector_shift_right(self, pos);
	self->pointer[pos] = *m;
	self->size += 1;
}

int vector_insert_sorted(vector_t *self, movie_t *m, int mode)
{
	field_t target = { 0 };
	field_t to_cmp = { 0 };
	field_from(&target, m, mode);
	int index = 0;
	int flag = 1;
	for (int i = 0; i < self->size && flag; i++)
	{
		field_from(&to_cmp, self->pointer + i, mode);
		index = i;
		if (field_cmp(&to_cmp, &target) > 0)
			flag = 0;
		else
			index++;
	}
	vector_insert(self, m, index);
	return self->size;
}

int vector_find(vector_t *self, int n, field_t *target, int mode)
{
	int low = 0;
	int high = n;
	int mid;
	field_t to_cmp = { 0 };
	int found = 0;
	movie_t *arr = self->pointer;

	while (low <= high && !found)
	{
		mid = (low + high) / 2;
		field_from(&to_cmp, arr + mid, mode);
		if (field_cmp(&to_cmp, target) == 0)
			found = 1;
		else if (field_cmp(&to_cmp, target) < 0)
			low = mid + 1;
		else if (field_cmp(&to_cmp, target) > 0)
			high = mid - 1;
	}
	return found ? mid : -1;
}

void vector_print(vector_t *self)
{
	for (int i = 0; i < self->size; ++i)
	{
		movie_print(self->pointer + i);
	}
}


vector_t read_all_movies(FILE *f, int mode, int *ec)
{
	int count = 0;
	movie_t m;
	int blank_encountered = 0;
	vector_t self = vector_new(1);
	while (!feof(f) && !(*ec) && !blank_encountered)
	{
		m = movie_read(f, ec);
		if (*ec == blank_movie)
			blank_encountered = 1;
		else
		{
			vector_insert_sorted(&self, &m, mode);
			count++;
		}
	}
	if (blank_encountered)
		*ec = 0;
	return self;
}
