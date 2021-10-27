//
// Created by dev on 10/17/21.
//

#include "util.h"
#include "../inc/matrix.h"
#include "../inc/check_main.h"

START_TEST(test_read_1)
{
	FILE *f = fopen("./unit_tests/input/matr_empty.txt", "r");
	int ec = 0;
	matrix_t res = matrix_from_file(f, &ec);
	ck_assert_int_ne(ec, 0);
	fclose(f);
	matrix_delete(&res);
}

END_TEST

START_TEST(test_read_2)
{
	FILE *f = fopen("./unit_tests/input/matr_1.txt", "r");
	double target_arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int ec = 0;
	matrix_t target = matrix_from_array(target_arr, 3, 3, &ec);
	matrix_t m = matrix_from_file(f, &ec);
	ck_assert_int_eq(ec, 0);
	ck_assert(matrix_eq(&m, &target));
	matrix_delete(&target);
	matrix_delete(&m);
	fclose(f);
}

END_TEST


START_TEST(test_matrix_create)
{
	double arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int ec = 0;
	matrix_t m = matrix_from_array(arr, 3, 3, &ec);
	ck_assert_int_eq(ec, 0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			ck_assert_double_eq(m.data[i][j], arr[i * 3 + j]);
		}
	}
	matrix_delete(&m);
}

END_TEST

Suite *matrix_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("read numbers");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_read_1);
	tcase_add_test(tc_core, test_read_2);
	tcase_add_test(tc_core, test_matrix_create);
	suite_add_tcase(s, tc_core);

	return s;
}