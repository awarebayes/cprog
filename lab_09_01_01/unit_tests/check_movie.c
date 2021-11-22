//
// Created by dev on 30/10/2021.
//
#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "movie.h"
#include "util.h"

START_TEST(test_movie_read_1)
{
	FILE *f = fopen("./unit_tests/input/movie.txt", "r");
	int ec = 0;
	ck_assert_ptr_nonnull(f);
	movie_t m = movie_read(f, &ec);
	ck_assert_int_eq(ec, ok);
	ck_assert_str_eq(m.title, "title");
	ck_assert_str_eq(m.name, "name");
	ck_assert_int_eq(m.year, 1234);
	fclose(f);
	movie_delete(&m);
}
END_TEST


START_TEST(test_movie_read_2)
{
	FILE *f = fopen("./unit_tests/input/movie_blank.txt", "r");
	int ec = 0;
	ck_assert_ptr_nonnull(f);
	movie_t m = movie_read(f, &ec);
	ck_assert_int_eq(ec, blank_movie);
	fclose(f);
	movie_delete(&m);
}
END_TEST


START_TEST(test_field_from)
{
	movie_t m  = {.title = "title", .name = "name", .year = 1234};

	field_t f = { 0 };
	field_from(&f, &m, f_name);
	ck_assert_str_eq(f.data.string, "name");
	ck_assert_int_eq(f.type, f_name);
	field_from(&f, &m, f_title);
	ck_assert_str_eq(f.data.string, "title");
	ck_assert_int_eq(f.type, f_title);
	field_from(&f, &m, f_year);
	ck_assert_int_eq(f.data.number, 1234);
	ck_assert_int_eq(f.type, f_year);
}
END_TEST


START_TEST(test_field_from_str)
{
	int ec = 0;
	field_t f = { 0 };
	f = field_from_str("name", f_name, &ec);
	ck_assert_str_eq(f.data.string, "name");
	ck_assert_int_eq(f.type, f_name);
	ck_assert_int_eq(ec, 0);
	f = field_from_str("title", f_title, &ec);
	ck_assert_str_eq(f.data.string, "title");
	ck_assert_int_eq(f.type, f_title);
	ck_assert_int_eq(ec, 0);
	f = field_from_str("1234", f_year, &ec);
	ck_assert_int_eq(f.data.number, 1234);
	ck_assert_int_eq(f.type, f_year);
	ck_assert_int_eq(ec, 0);
	f = field_from_str("abcde", f_year, &ec);
	ck_assert_int_eq(ec, read_error);
}
END_TEST


START_TEST(test_field_cmp)
{
	int ec = 0;
	field_t f1 = { 0 };
	field_t f2 = { 0 };
	f1 = field_from_str("name", f_name, &ec);
	f2 = field_from_str("name", f_name, &ec);
	ck_assert_int_eq(field_cmp(&f1, &f2), 0);
	ck_assert_int_eq(ec, 0);

	f1 = field_from_str("1234", f_year, &ec);
	f2 = field_from_str("1234", f_year, &ec);
	ck_assert_int_eq(field_cmp(&f1, &f2), 0);
	ck_assert_int_eq(ec, 0);
}
END_TEST

START_TEST(test_get_field_type)
{
	ck_assert_int_eq(get_field_index("name"), f_name);
	ck_assert_int_eq(get_field_index("title"), f_title);
	ck_assert_int_eq(get_field_index("year"), f_year);
}
END_TEST

Suite *movie_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Movie suite");
	tc_core = tcase_create("movie");
	tcase_add_test(tc_core, test_movie_read_1);
	tcase_add_test(tc_core, test_movie_read_2);
	tcase_add_test(tc_core, test_field_from);
	tcase_add_test(tc_core, test_field_from_str);
	tcase_add_test(tc_core, test_field_cmp);
	tcase_add_test(tc_core, test_get_field_type);
	suite_add_tcase(s, tc_core);

	return s;
}
