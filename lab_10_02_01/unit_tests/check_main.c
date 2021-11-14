#include <check.h>
#include "node.h"
#include "util.h"

START_TEST(test_read_arr_int)
{
	int arr_out[10];
	int str_in = "1 2 3 4 5 6 7 8 9 10";
	int target[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int size = 0;
	int size_target = 10;
	read_
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

