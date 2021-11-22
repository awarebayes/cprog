#include "util.h"
#include "check_main.h"
#include <stdlib.h>
#include <stdio.h>
#include <check.h>

START_TEST(test_remove_lc)
{
	char string_with_n[] = "aboba\n";
	remove_lc(string_with_n);
	ck_assert_int_eq(strcmp(string_with_n, "aboba"), 0);
}

END_TEST


START_TEST(test_all_digits_1)
{
	char string[] = "1234";
	ck_assert_int_eq(all_digits(string), 1);
}

END_TEST

START_TEST(test_all_digits_2)
{
	char string[] = "1234a";
	ck_assert_int_eq(all_digits(string), 0);
}

END_TEST

START_TEST(test_all_space_1)
{
	char string[] = "\t ";
	ck_assert_int_eq(all_space(string), 1);
}

END_TEST


START_TEST(test_all_space_2)
{
	char string[] = "\t   ";
	ck_assert_int_eq(all_space(string), 1);
}

END_TEST


START_TEST(test_read_string_1)
{
	char *target = NULL;
	FILE *f = fopen("./unit_tests/input/empty_file.txt", "r");
	int ec = 0;
	ck_assert_ptr_nonnull(f);
	read_string(f, &target, &ec);
	ck_assert_int_eq(ec, read_error);
	free(target);
	fclose(f);
}

END_TEST

START_TEST(test_read_string_2)
{
	char *target = NULL;
	FILE *f = fopen("./unit_tests/input/test_string.txt", "r");
	int ec = 0;
	ck_assert_ptr_nonnull(f);
	read_string(f, &target, &ec);
	ck_assert_int_eq(ec, ok);
	ck_assert_str_eq(target, "test string");
	free(target);
	fclose(f);
}

END_TEST



START_TEST(test_read_year_1)
{
	int target = -1;
	FILE *f = fopen("./unit_tests/input/year_good.txt", "r");
	int ec = 0;
	ck_assert_ptr_nonnull(f);
	read_year(f, &target, &ec);
	ck_assert_int_eq(ec, ok);
	ck_assert_int_eq(target, 1234);
	fclose(f);
}

END_TEST


START_TEST(test_read_year_2)
{
	int target = -1;
	FILE *f = fopen("./unit_tests/input/year_bad.txt", "r");
	int ec = 0;
	ck_assert_ptr_nonnull(f);
	read_year(f, &target, &ec);
	ck_assert_int_eq(ec, read_error);
	fclose(f);
}

END_TEST


START_TEST(test_int_cmp)
{
	ck_assert_int_eq(int_cmp(0, 0), 0);
}

END_TEST

Suite *util_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Util suite");
	tc_core = tcase_create("util");

	tcase_add_test(tc_core, test_remove_lc);
	tcase_add_test(tc_core, test_all_digits_1);
	tcase_add_test(tc_core, test_all_digits_2);
	tcase_add_test(tc_core, test_all_space_1);
	tcase_add_test(tc_core, test_all_space_2);
	tcase_add_test(tc_core, test_read_string_1);
	tcase_add_test(tc_core, test_read_string_2);
	tcase_add_test(tc_core, test_read_year_1);
	tcase_add_test(tc_core, test_read_year_2);
	tcase_add_test(tc_core, test_int_cmp);
	suite_add_tcase(s, tc_core);

	return s;
}