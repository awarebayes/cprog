//
// Created by dev on 30/10/2021.
//

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "movie.h"
#include "movie_vector.h"
#include "util.h"


START_TEST(test_vector_create)
{
	movie_t blank = { 0 };
	vector_t vector = vector_new(8);
	ck_assert_int_eq(vector.size, 0);
	ck_assert_int_eq(vector.capacity, 8);
	vector_insert(&vector, &blank, 0);
	ck_assert_int_eq(vector.capacity, 8);
	ck_assert_mem_eq(vector.pointer, &blank, sizeof(movie_t));
	vector_delete(&vector);
}

END_TEST

START_TEST(test_vector_realloc)
{
	movie_t m1 = { .year=1 };
	movie_t m2 = { .year=2 };
	movie_t m3 = { .year=3 };
	vector_t vector = vector_new(8);
	ck_assert_int_eq(vector.size, 0);
	ck_assert_int_eq(vector.capacity, 8);
	vector_insert(&vector, &m1, 0);
	vector_insert(&vector, &m2, 1);
	vector_insert(&vector, &m3, 2);
	ck_assert_int_eq(vector.capacity, 8);
	vector_realloc(&vector);
	ck_assert_mem_eq(vector.pointer, &m1, sizeof(movie_t));
	ck_assert_mem_eq(vector.pointer + 1, &m2, sizeof(movie_t));
	ck_assert_mem_eq(vector.pointer + 2, &m3, sizeof(movie_t));
	vector_delete(&vector);
}

END_TEST

START_TEST(test_vector_grow_get)
{
	movie_t m1 = { .year=1 };
	movie_t m2 = { .year=2 };
	movie_t m3 = { .year=3 };
	vector_t vector = vector_new(1);
	ck_assert_int_eq(vector.size, 0);
	ck_assert_int_eq(vector.capacity, 1);
	vector_insert(&vector, &m1, 0);
	ck_assert_int_eq(vector.capacity, 2);
	vector_insert(&vector, &m2, 1);
	ck_assert_int_eq(vector.capacity, 4);
	vector_insert(&vector, &m3, 2);
	ck_assert_mem_eq(vector_get(&vector, 0), &m1, sizeof(movie_t));
	ck_assert_mem_eq(vector_get(&vector, 1), &m2, sizeof(movie_t));
	ck_assert_mem_eq(vector_get(&vector, 2), &m3, sizeof(movie_t));
	vector_delete(&vector);
}

END_TEST

START_TEST(test_vector_shift_right)
{
	movie_t m1 = { .year=1 };
	movie_t m2 = { .year=2 };
	vector_t vector = vector_new(4);
	vector.size = 2;
	vector.pointer[0] = m1;
	vector_shift_right(&vector, 0);
	vector.pointer[0] = m2;
	ck_assert_mem_eq(vector_get(&vector, 0), &m2, sizeof(movie_t));
	ck_assert_mem_eq(vector_get(&vector, 1), &m1, sizeof(movie_t));
	vector_delete(&vector);
}

END_TEST

START_TEST(test_vector_insert_sorted)
{
	movie_t m1 = { .year=1 };
	movie_t m2 = { .year=-3 };
	movie_t m3 = { .year=5 };
	movie_t m4 = { .year=-9 };
	vector_t vector = vector_new(6);
	vector_insert_sorted(&vector, &m3, f_year);
	vector_insert_sorted(&vector, &m2, f_year);
	vector_insert_sorted(&vector, &m4, f_year);
	vector_insert_sorted(&vector, &m1, f_year);
	ck_assert_mem_eq(vector_get(&vector, 0), &m4, sizeof(movie_t));
	ck_assert_mem_eq(vector_get(&vector, 1), &m2, sizeof(movie_t));
	ck_assert_mem_eq(vector_get(&vector, 2), &m1, sizeof(movie_t));
	ck_assert_mem_eq(vector_get(&vector, 3), &m3, sizeof(movie_t));
	vector_delete(&vector);
}

END_TEST


START_TEST(test_vector_find)
{
	movie_t m1 = { .year=1 };
	movie_t m2 = { .year=-3 };
	movie_t m3 = { .year=5 };
	movie_t m4 = { .year=-9 };
	vector_t vector = vector_new(6);
	vector_insert_sorted(&vector, &m1, f_year);
	vector_insert_sorted(&vector, &m2, f_year);
	vector_insert_sorted(&vector, &m3, f_year);
	vector_insert_sorted(&vector, &m4, f_year);
	field_t f0 = field_from_str("-9", f_year, NULL);
	field_t f1 = field_from_str("-3", f_year, NULL);
	field_t f2 = field_from_str("1", f_year, NULL);
	field_t f3 = field_from_str("5", f_year, NULL);

	ck_assert_int_eq(vector_find(&vector, &f0, f_year), 0);
	ck_assert_int_eq(vector_find(&vector, &f1, f_year), 1);
	ck_assert_int_eq(vector_find(&vector, &f2, f_year), 2);
	ck_assert_int_eq(vector_find(&vector, &f3, f_year), 3);

	vector_delete(&vector);
}

END_TEST

Suite *movie_vector_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Movie vector suite");
	tc_core = tcase_create("movie vector");
	tcase_add_test(tc_core, test_vector_create);
	tcase_add_test(tc_core, test_vector_realloc);
	tcase_add_test(tc_core, test_vector_grow_get);
	tcase_add_test(tc_core, test_vector_shift_right);
	tcase_add_test(tc_core, test_vector_insert_sorted);
	tcase_add_test(tc_core, test_vector_find);
	suite_add_tcase(s, tc_core);

	return s;
}
