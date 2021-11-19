#include <check.h>
#include "mylist.h"

int comparator(const void *a, const void *b)
{
	return *((int *) a) - *((int *) b) < 0;
}

START_TEST(test_list_find)
{
	int numbers[] = { 1, 2, 3 };
	node_t *n1 = node_new(&numbers[0], NULL);
	node_t *n2 = node_new(&numbers[1], NULL);
	node_t *n3 = node_new(&numbers[2], NULL);
	n1->next = n2;
	n2->next = n3;

	// ---
	int number = 1;
	node_t *res = find(n1, &number, comparator);
	ck_assert_ptr_eq(res, n1);
	// ---
	number = 2;
	res = find(n1, &number, comparator);
	ck_assert_ptr_eq(res, n2);
	// ---
	number = 3;
	res = find(n1, &number, comparator);
	ck_assert_ptr_eq(res, n3);
	// ---
	number = 4;
	res = find(n1, &number, comparator);
	ck_assert_ptr_eq(res, NULL);

	// free
	node_delete(n1);
	node_delete(n2);
	node_delete(n3);
}

END_TEST


START_TEST(test_list_pop_front)
{
	int numbers[] = { 1, 2, 3 };
	node_t *n1 = node_new(&numbers[0], NULL);
	node_t *n2 = node_new(&numbers[1], NULL);
	node_t *n3 = node_new(&numbers[2], NULL);
	n1->next = n2;
	n2->next = n3;

	void *pop_res = NULL;

	// ---
	pop_res = pop_front(&n1);
	ck_assert_ptr_eq(n1, n2);
	ck_assert_int_eq((*(int *) pop_res), numbers[0]);


	pop_res = pop_front(&n1);
	ck_assert_ptr_eq(n1, n3);
	ck_assert_int_eq((*(int *) pop_res), numbers[1]);

	pop_res = pop_front(&n1);
	ck_assert_ptr_eq(n1, NULL);
	ck_assert_int_eq((*(int *) pop_res), numbers[2]);

	pop_res = pop_front(&n1);
	ck_assert_ptr_eq(n1, NULL);
	ck_assert_ptr_eq(pop_res, NULL);
}

END_TEST


START_TEST(test_list_copy)
{
	int numbers[] = { 1, 2, 3 };
	node_t *n1 = node_new(&numbers[0], NULL);
	node_t *n2 = node_new(&numbers[1], NULL);
	node_t *n3 = node_new(&numbers[2], NULL);
	n1->next = n2;
	n2->next = n3;
	// ---

	node_t *old = n1;
	node_t *new = NULL;
	copy(old, &new);

	node_t *new_handle = new;
	node_t *old_handle = old;

	while (old && new)
	{
		int old_value = *((int *) old->data);
		int new_value = *((int *) new->data);
		ck_assert_int_eq(old_value, new_value);
		old = old->next;
		new = new->next;
	}

	ck_assert_ptr_eq(old, NULL);
	ck_assert_ptr_eq(new, NULL);
	// free
	list_delete(new_handle);
	list_delete(old_handle);
}

END_TEST


START_TEST(test_list_sorted_insert_1)
{
	node_t *head = NULL;
	int array[] = { 2, 4, 6, 8, 10 };
	// ---
	for (int i = 0; i < 5; i++)
	{
		node_t *node = node_new(&array[i], NULL);
		sorted_insert(&head, node, comparator);
	}


	void *pop_res = 0;
	for (int i = 0; i < 5; i++)
	{
		pop_res = pop_front(&head);
		ck_assert_int_eq((*(int *) pop_res), array[i]);
		ck_assert_ptr_eq(((int *) pop_res), array + i);
	}

	// free
	list_delete(head);
}

END_TEST


START_TEST(test_list_sorted_insert_2)
{
	node_t *head = NULL;
	int array1[] = { 2, 4, 6, 8, 10 };
	int array2[] = { 1, 3, 5, 7, 9 };
	int array_target[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// ---
	for (int i = 0; i < 5; i++)
	{
		node_t *node = node_new(&array1[i], NULL);
		sorted_insert(&head, node, comparator);
	}

	for (int i = 0; i < 5; i++)
	{
		node_t *node = node_new(&array2[i], NULL);
		sorted_insert(&head, node, comparator);
	}

	void *pop_res = 0;
	for (int i = 0; i < 10; i++)
	{
		pop_res = pop_front(&head);
		ck_assert_int_eq((*(int *) pop_res), array_target[i]);
	}

	// free
	list_delete(head);
}

END_TEST

START_TEST(test_list_insert_sorted_3)
{
	node_t *head = NULL;
	int array1[] = { 9, 2, 3, 5, 4, 8, 7, 0, 6, 1 };
	int array_target[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	// ---
	for (int i = 0; i < 10; i++)
	{
		node_t *node = node_new(&array1[i], NULL);
		sorted_insert(&head, node, comparator);
	}

	void *pop_res = 0;
	for (int i = 0; i < 10; i++)
	{
		pop_res = pop_front(&head);
		ck_assert_int_eq((*(int *) pop_res), array_target[i]);
	}

	// free
	list_delete(head);
}

END_TEST


START_TEST(test_list_sort)
{
	node_t *head = NULL;
	int array1[] = { 9, 2, 3, 5, 4, 8, 7, 0, 6, 1 };
	int array_target[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	node_t *prev = NULL;
	// ---
	for (int i = 0; i < 10; i++)
	{
		node_t *node = node_new(&array1[i], NULL);
		if (prev)
			prev->next = node;
		else
			head = node;
		prev = node;
	}

	node_t *new_sorted = sort(head, comparator);
	void *pop_res = 0;
	for (int i = 0; i < 10; i++)
	{
		pop_res = pop_front(&new_sorted);
		ck_assert_int_eq((*(int *) pop_res), array_target[i]);
	}

	// free
	list_delete(new_sorted);
}

END_TEST

Suite *list_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("List suite");
	tc_core = tcase_create("list");

	tcase_add_test(tc_core, test_list_find);
	tcase_add_test(tc_core, test_list_pop_front);
	tcase_add_test(tc_core, test_list_copy);
	tcase_add_test(tc_core, test_list_sorted_insert_1);
	tcase_add_test(tc_core, test_list_sorted_insert_2);
	tcase_add_test(tc_core, test_list_insert_sorted_3);
	tcase_add_test(tc_core, test_list_sort);
	suite_add_tcase(s, tc_core);

	return s;
}

int main()
{
	int number_failed = 0;
	SRunner *sr;
	sr = srunner_create(list_suite());
	srunner_set_fork_status(sr, CK_NOFORK);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed != 0);
}

