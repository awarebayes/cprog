#include "util.h"
#include "check_main.h"
#include <stdlib.h>
#include <check.h>

START_TEST(test_remove_lc)
{
	char string_with_n[] = "aboba\n";
	remove_lc(string_with_n);
	ck_assert_int_eq(strcmp(string_with_n, "aboba"), 0);
}
END_TEST


Suite *util_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Util suite");
	tc_core = tcase_create("util");

	tcase_add_test(tc_core, test_remove_lc);
	suite_add_tcase(s, tc_core);

	return s;
}