#include "util.h"
#include "matrix.h"
#include "check_main.h"
#include <stdlib.h>

START_TEST(test_fcmp_1)
{
	int res = fcmp(1.0, 0.0);
	ck_assert_int_eq(res, 1);
}

END_TEST


START_TEST(test_fcmp_2)
{
	int res = fcmp(0.0, 1.0);
	ck_assert_int_eq(res, -1);
}

END_TEST


START_TEST(test_fcmp_3)
{
	int res = fcmp(0.0, 0.0);
	ck_assert_int_eq(res, 0);
}

END_TEST


START_TEST(test_read_arr)
{
	FILE *f = fopen("./unit_tests/input/arr.txt", "r");
	int ec = 0;
	double *arr = read_arr(f, 4, &ec);
	double target[] = { 1, 2, 3, 4 };
	ck_assert_int_eq(ec, 0);
	ck_assert_mem_eq(arr, target, sizeof(double) * 4);
	free(arr);
	fclose(f);
}

END_TEST

Suite *util_suite(void)
{
	Suite *s;
	TCase *tc_fcmp;
	TCase *tc_read;

	s = suite_create("Util suite");
	tc_fcmp = tcase_create("fcmp");
	tc_read = tcase_create("read");

	tcase_add_test(tc_fcmp, test_fcmp_1);
	tcase_add_test(tc_fcmp, test_fcmp_2);
	tcase_add_test(tc_fcmp, test_fcmp_3);
	tcase_add_test(tc_read, test_read_arr);
	suite_add_tcase(s, tc_fcmp);
	suite_add_tcase(s, tc_read);

	return s;
}