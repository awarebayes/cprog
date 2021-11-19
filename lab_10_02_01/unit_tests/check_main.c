#include <check.h>
#include "node.h"
#include "util.h"
#include "poly.h"

START_TEST(test_read_arr_int)
{
	int arr_out[10];
	char str_in[] = "1 2 3 4 5 6 7 8 9 10";
	int max_size = 10;
	int target[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int size = 0;
	int size_target = 10;
	int ec = 0;
	read_int_array(arr_out, &size, max_size, str_in, &ec);

	ck_assert_int_eq(size, size_target);
	ck_assert_int_eq(ec, ok);
	ck_assert_mem_eq(target, arr_out, sizeof(int) * 10);
}

END_TEST

START_TEST(test_read_arr_int_2)
{
	int arr_out[11];
	int max_size = 11;
	char str_in[] = "1 2 3 4 5 6 7 8 9 10   ";
	int target[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int size = 0;
	int size_target = 10;
	int ec = 0;
	read_int_array(arr_out, &size, max_size, str_in, &ec);

	ck_assert_int_eq(size, size_target);
	ck_assert_int_eq(ec, ok);
	ck_assert_mem_eq(target, arr_out, sizeof(int) * 10);
}

END_TEST


START_TEST(test_read_arr_int_3)
{
	int arr_out[10];
	int max_size = 8;
	char str_in[] = "1 2 3 4 5 6 7 8 9 10   ";
	int size = 0;
	int ec = 0;
	read_int_array(arr_out, &size, max_size, str_in, &ec);
	ck_assert_int_eq(ec, input_array_overflow_err);
}

END_TEST


START_TEST(test_poly_eval_1)
{
	char poly[] = "1 1";
	int ec = ok;
	poly_t p = poly_from_string(poly, &ec);
	int res = poly_eval(&p, 1, &ec);
	ck_assert_int_eq(res, 1);
	poly_delete(&p);
}

END_TEST


START_TEST(test_poly_eval_2)
{
	char poly[] = "1 1";
	int ec = ok;
	poly_t p = poly_from_string(poly, &ec);
	int res = poly_eval(&p, 100, &ec);
	ck_assert_int_eq(res, 100);
	poly_delete(&p);
}

END_TEST


START_TEST(test_poly_eval_3)
{
	char poly[] = "1 2 2 1 3 0";
	int ec = ok;
	poly_t p = poly_from_string(poly, &ec);
	int res = poly_eval(&p, 100, &ec);
	ck_assert_int_eq(res, 10203);
	poly_delete(&p);
}

END_TEST


START_TEST(test_poly_from_string_1)
{
	char poly[] = "1 2 2 1 3 1";
	int ec = ok;
	poly_t p = poly_from_string(poly, &ec);
	ck_assert_int_eq(ec, input_err);
	poly_delete(&p);
}

END_TEST


START_TEST(test_poly_from_srting_2)
{
	char poly[] = "1 2 2 1 0 -1";
	int ec = ok;
	poly_t p = poly_from_string(poly, &ec);
	//ck_assert_int_eq(ec, input_err);
	poly_delete(&p);
}

END_TEST


START_TEST(test_term_derivative_1)
{
	term_t t = { .coef = 2, .pow = 2 };
	term_t dt_dx = term_derivative(&t);
	ck_assert_int_eq(dt_dx.coef, 4);
	ck_assert_int_eq(dt_dx.pow, 1);
}

END_TEST


START_TEST(test_term_derivative_2)
{
	term_t t = { .coef = 2, .pow = 0 };
	term_t dt_dx = term_derivative(&t);
	ck_assert_int_eq(dt_dx.coef, 0);
	ck_assert_int_eq(dt_dx.pow, 0);
	ck_assert(term_zero(&dt_dx));
}

END_TEST


START_TEST(test_poly_equal_1)
{
	int ec = ok;

	char p1str[] = "4 4 3 3 2 2 1 1";
	char p2str[] = "4 4 3 3 2 2 1 1";
	poly_t p1 = poly_from_string(p1str, &ec);
	poly_t p2 = poly_from_string(p2str, &ec);
	ck_assert(!ec);
	ck_assert(poly_equal(&p1, &p2));
	poly_delete(&p1);
	poly_delete(&p2);
}

END_TEST

START_TEST(test_poly_equal_2)
{
	int ec = ok;
	char p1str[] = "4 4 3 3 2 2 1 1";
	char p2str[] = "4 4 3 3 2 2 1 1 0 0";
	poly_t p1 = poly_from_string(p1str, &ec);
	poly_t p2 = poly_from_string(p2str, &ec);
	ck_assert(!ec);
	ck_assert(!poly_equal(&p1, &p2));
	poly_delete(&p1);
	poly_delete(&p2);
}

END_TEST


START_TEST(test_poly_derivative_1)
{
	int ec = ok;
	char p1str[] = "4 4 3 3 2 2 1 1";
	char d2str[] = "16 3 9 2 4 1 1 0";
	poly_t p1 = poly_from_string(p1str, &ec);
	poly_t p1d = poly_derivative(&p1, &ec);
	poly_t p2 = poly_from_string(d2str, &ec);
	ck_assert(!ec);
	ck_assert(poly_equal(&p1d, &p2));
	poly_delete(&p1);
	poly_delete(&p1d);
	poly_delete(&p2);
}

END_TEST


START_TEST(test_poly_derivative_2)
{
	int ec = ok;
	char p1str[] = "4 4 3 3 2 2 1 1 5 0";
	char d2str[] = "16 3 9 2 4 1 1 0";
	poly_t p1 = poly_from_string(p1str, &ec);
	poly_t p1d = poly_derivative(&p1, &ec);
	poly_t p2 = poly_from_string(d2str, &ec);
	ck_assert(!ec);
	ck_assert(poly_equal(&p1d, &p2));
	poly_delete(&p1);
	poly_delete(&p1d);
	poly_delete(&p2);
}

END_TEST


START_TEST(test_poly_derivative_3)
{
	int ec = ok;
	char p1str[] = "5 0";
	poly_t p1 = poly_from_string(p1str, &ec);
	poly_t p1d = poly_derivative(&p1, &ec);
	ck_assert_int_eq(ec, 0);
	poly_delete(&p1);
	poly_delete(&p1d);
}

END_TEST


START_TEST(test_poly_sum_1)
{
	int ec = ok;
	char p1str[] = "1 3 5 0";
	char p2str[] = "1 3 5 0";
	char ptarget_str[] = "2 3 10 0";
	poly_t p1 = poly_from_string(p1str, &ec);
	poly_t p2 = poly_from_string(p2str, &ec);
	poly_t ptarget = poly_from_string(ptarget_str, &ec);
	poly_t psum = poly_sum(&p1, &p2, &ec);
	ck_assert_int_eq(ec, 0);
	ck_assert(poly_equal(&psum, &ptarget));
	poly_delete(&p1);
	poly_delete(&p2);
	poly_delete(&ptarget);
	poly_delete(&psum);
}

END_TEST


START_TEST(test_poly_sum_2)
{
	int ec = ok;
	char p1str[] = "1 3 5 0";
	char p2str[] = "4 2";
	char ptarget_str[] = "1 3 4 2 5 0";
	poly_t p1 = poly_from_string(p1str, &ec);
	poly_t p2 = poly_from_string(p2str, &ec);
	poly_t ptarget = poly_from_string(ptarget_str, &ec);
	poly_t psum = poly_sum(&p1, &p2, &ec);
	ck_assert_int_eq(ec, 0);
	ck_assert(poly_equal(&psum, &ptarget));
	poly_delete(&p1);
	poly_delete(&p2);
	poly_delete(&ptarget);
	poly_delete(&psum);
}

END_TEST


START_TEST(test_poly_sum_3)
{
	int ec = ok;
	char p1str[] = "4 2";
	char p2str[] = "1 3 5 0";
	char ptarget_str[] = "1 3 4 2 5 0";
	poly_t p1 = poly_from_string(p1str, &ec);
	poly_t p2 = poly_from_string(p2str, &ec);
	poly_t ptarget = poly_from_string(ptarget_str, &ec);
	poly_t psum = poly_sum(&p1, &p2, &ec);
	ck_assert_int_eq(ec, 0);
	ck_assert(poly_equal(&psum, &ptarget));
	poly_delete(&p1);
	poly_delete(&p2);
	poly_delete(&ptarget);
	poly_delete(&psum);
}

END_TEST


START_TEST(test_poly_odd_even_split)
{
	int ec = ok;
	char pstr[] = "4 4 3 3 2 2 1 1 5 0";
	char peven_str[] = "4 4 2 2 5 0";
	char podd_str[] = "3 3 1 1";
	poly_t p = poly_from_string(pstr, &ec);
	poly_t peven_target = poly_from_string(peven_str, &ec);
	poly_t podd_target = poly_from_string(podd_str, &ec);
	poly_t podd = { 0 };
	poly_t peven = { 0 };

	poly_split_odd_even_power(&p, &podd, &peven, &ec);

	ck_assert(!ec);
	ck_assert(poly_equal(&peven_target, &peven));
	ck_assert(poly_equal(&podd_target, &podd));
	poly_delete(&p);
	poly_delete(&peven_target);
	poly_delete(&podd_target);
	poly_delete(&peven);
	poly_delete(&podd);
}

END_TEST

Suite *util_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("util suite");
	tc_core = tcase_create("util");

	tcase_add_test(tc_core, test_read_arr_int);
	tcase_add_test(tc_core, test_read_arr_int_2);
	tcase_add_test(tc_core, test_read_arr_int_3);
	tcase_add_test(tc_core, test_poly_eval_1);
	tcase_add_test(tc_core, test_poly_eval_2);
	tcase_add_test(tc_core, test_poly_eval_3);
	tcase_add_test(tc_core, test_poly_from_string_1);
	tcase_add_test(tc_core, test_poly_from_srting_2);
	tcase_add_test(tc_core, test_term_derivative_1);
	tcase_add_test(tc_core, test_term_derivative_2);
	tcase_add_test(tc_core, test_poly_equal_1);
	tcase_add_test(tc_core, test_poly_equal_2);
	tcase_add_test(tc_core, test_poly_derivative_1);
	tcase_add_test(tc_core, test_poly_derivative_2);
	tcase_add_test(tc_core, test_poly_derivative_3);
	tcase_add_test(tc_core, test_poly_sum_1);
	tcase_add_test(tc_core, test_poly_sum_2);
	tcase_add_test(tc_core, test_poly_sum_3);
	tcase_add_test(tc_core, test_poly_odd_even_split);
	suite_add_tcase(s, tc_core);

	return s;
}

int main()
{
	int number_failed = 0;
	SRunner *sr;
	sr = srunner_create(util_suite());
	srunner_set_fork_status(sr, CK_NOFORK);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed != 0);
}

