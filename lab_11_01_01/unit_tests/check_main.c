#include <check.h>
#include <stdio.h>
#include <limits.h>
#include "my_printf.h"

START_TEST(test_printf_1)
{
	int buf_size = 500;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world!";

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_str_eq(buf, target_buf);
	ck_assert_int_eq(printed_target, printed_my);
}

END_TEST


START_TEST(test_printf_2)
{
	int buf_size = 500;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world!\n";

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_str_eq(buf, target_buf);
	ck_assert_int_eq(printed_target, printed_my);
}

END_TEST


START_TEST(test_printf_3)
{
	int buf_size = 500;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "\\ \'Hello\", world!\n";

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_4)
{
	int buf_size = 500;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 1);
	int printed_my = my_snprintf(buf, buf_size, fmt, 1);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_5)
{
	int buf_size = 500;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d %d %c\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 1, 2, '3');
	int printed_my = my_snprintf(buf, buf_size, fmt, 1, 2, '3');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_6)
{
	int buf_size = 13;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d %d %c\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 1, 2, '3');
	int printed_my = my_snprintf(buf, buf_size, fmt, 1, 2, '3');

	ck_assert_str_eq(buf, target_buf);
	ck_assert_int_eq(printed_target, printed_my);
}

END_TEST


START_TEST(test_printf_7)
{
	int buf_size = 15;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d %d %c\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 1, 2, '3');
	int printed_my = my_snprintf(buf, buf_size, fmt, 1, 2, '3');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_8)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d %d %c\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 123, 2, '3');
	int printed_my = my_snprintf(buf, buf_size, fmt, 123, 2, '3');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_9)
{
	int buf_size = 17;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d %d %c\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 123, 2, '3');
	int printed_my = my_snprintf(buf, buf_size, fmt, 123, 2, '3');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_10)
{
	int buf_size = 18;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d %d %c\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 123, 123, '3');
	int printed_my = my_snprintf(buf, buf_size, fmt, 123, 123, '3');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST

START_TEST(test_printf_11)
{
	int buf_size = 19;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %d %d %c\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 123, 123, '3');
	int printed_my = my_snprintf(buf, buf_size, fmt, 123, 123, '3');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_12)
{
	int buf_size = 13;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %s\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, "123");
	int printed_my = my_snprintf(buf, buf_size, fmt, "123");

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_13)
{
	int buf_size = 14;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %s\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, "123");
	int printed_my = my_snprintf(buf, buf_size, fmt, "123");

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_14)
{
	int buf_size = 15;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %s\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, "123");
	int printed_my = my_snprintf(buf, buf_size, fmt, "123");

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_15)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "Hello, world! %c %d %s\n";

	int printed_target = snprintf(target_buf, buf_size, fmt, 'c', 198, "123");
	int printed_my = my_snprintf(buf, buf_size, fmt, 'c', 198, "123");

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_16)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%s";

	int printed_target = snprintf(target_buf, buf_size, fmt, "123");
	int printed_my = my_snprintf(buf, buf_size, fmt, "123");

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_17)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%c";

	int printed_target = snprintf(target_buf, buf_size, fmt, 'a');
	int printed_my = my_snprintf(buf, buf_size, fmt, 'a');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_18)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%d";

	int printed_target = snprintf(target_buf, buf_size, fmt, INT_MIN);
	int printed_my = my_snprintf(buf, buf_size, fmt, INT_MIN);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_19)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%d";

	int printed_target = snprintf(target_buf, buf_size, fmt, INT_MAX);
	int printed_my = my_snprintf(buf, buf_size, fmt, INT_MAX);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_20)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%d";

	int printed_target = snprintf(target_buf, buf_size, fmt, INT_MIN);
	int printed_my = my_snprintf(buf, buf_size, fmt, INT_MIN);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST

START_TEST(test_printf_21)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%d";

	int printed_target = snprintf(target_buf, buf_size, fmt, 0);
	int printed_my = my_snprintf(buf, buf_size, fmt, 0);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_22)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%d";

	int printed_target = snprintf(target_buf, buf_size, fmt, -1);
	int printed_my = my_snprintf(buf, buf_size, fmt, -1);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_23)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%o";

	int printed_target = snprintf(target_buf, buf_size, fmt, -1);
	int printed_my = my_snprintf(buf, buf_size, fmt, -1);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_24)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%o";

	int printed_target = snprintf(target_buf, buf_size, fmt, 0);
	int printed_my = my_snprintf(buf, buf_size, fmt, 0);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST

START_TEST(test_printf_25)
{
	int buf_size = 16;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%o";

	int printed_target = snprintf(target_buf, buf_size, fmt, 1234);
	int printed_my = my_snprintf(buf, buf_size, fmt, 1234);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_26)
{
	int buf_size = 29;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%o";

	int printed_target = snprintf(target_buf, buf_size, fmt, -1234);
	int printed_my = my_snprintf(buf, buf_size, fmt, -1234);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_27)
{
	int buf_size = 24;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "test %d";

	int printed_target = snprintf(target_buf, buf_size, fmt, INT_MAX);
	int printed_my = my_snprintf(buf, buf_size, fmt, INT_MAX);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST

START_TEST(test_printf_28)
{
	int buf_size = 28;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%d test";

	int printed_target = snprintf(target_buf, buf_size, fmt, INT_MAX);
	int printed_my = my_snprintf(buf, buf_size, fmt, INT_MAX);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST

START_TEST(test_printf_29)
{
	int buf_size = 22;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%d test";

	int printed_target = snprintf(target_buf, buf_size, fmt, INT_MIN);
	int printed_my = my_snprintf(buf, buf_size, fmt, INT_MIN);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_30)
{
	int buf_size = 22;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%%";

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_31)
{
	int buf_size = 22;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%% %s";

	int printed_target = snprintf(target_buf, buf_size, fmt, "123");
	int printed_my = my_snprintf(buf, buf_size, fmt, "123");

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_32)
{
	int buf_size = 1;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%c";

	int printed_target = snprintf(target_buf, buf_size, fmt, '%');
	int printed_my = my_snprintf(buf, buf_size, fmt, '%');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_33)
{
	int buf_size = 2;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%c";

	int printed_target = snprintf(target_buf, buf_size, fmt, '%');
	int printed_my = my_snprintf(buf, buf_size, fmt, '%');

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST


START_TEST(test_printf_34)
{
	int buf_size = 1;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%d";

	int printed_target = snprintf(target_buf, buf_size, fmt, 1);
	int printed_my = my_snprintf(buf, buf_size, fmt, 1);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);
}

END_TEST

START_TEST(test_printf_35)
{
	int buf_size = 5;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%%%% %%a";

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);

}

END_TEST


START_TEST(test_printf_36)
{
	int buf_size = 5;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "";

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);

}

END_TEST


START_TEST(test_printf_37)
{
	int buf_size = 5;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "%";

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);

}

END_TEST



START_TEST(test_printf_38)
{
	int buf_size = 5;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = "asdasd %";

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);

}

END_TEST

START_TEST(test_printf_39)
{
	int buf_size = 5;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = NULL;

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);

}

END_TEST


START_TEST(test_printf_40)
{
	int buf_size = 5;
	char buf[buf_size];
	char target_buf[buf_size];
	char *fmt = NULL;

	int printed_target = snprintf(target_buf, buf_size, fmt);
	int printed_my = my_snprintf(buf, buf_size, fmt);

	ck_assert_int_eq(printed_target, printed_my);
	ck_assert_str_eq(buf, target_buf);

}
END_TEST


Suite *printf_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("printf suite");
	tc_core = tcase_create("printf");

	tcase_add_test(tc_core, test_printf_1);
	tcase_add_test(tc_core, test_printf_2);
	tcase_add_test(tc_core, test_printf_3);
	tcase_add_test(tc_core, test_printf_4);
	tcase_add_test(tc_core, test_printf_5);
	tcase_add_test(tc_core, test_printf_6);
	tcase_add_test(tc_core, test_printf_7);
	tcase_add_test(tc_core, test_printf_8);
	tcase_add_test(tc_core, test_printf_9);
	tcase_add_test(tc_core, test_printf_10);
	tcase_add_test(tc_core, test_printf_11);
	tcase_add_test(tc_core, test_printf_12);
	tcase_add_test(tc_core, test_printf_13);
	tcase_add_test(tc_core, test_printf_14);
	tcase_add_test(tc_core, test_printf_15);
	tcase_add_test(tc_core, test_printf_16);
	tcase_add_test(tc_core, test_printf_17);
	tcase_add_test(tc_core, test_printf_18);
	tcase_add_test(tc_core, test_printf_19);
	tcase_add_test(tc_core, test_printf_20);
	tcase_add_test(tc_core, test_printf_21);
	tcase_add_test(tc_core, test_printf_22);
	tcase_add_test(tc_core, test_printf_23);
	tcase_add_test(tc_core, test_printf_24);
	tcase_add_test(tc_core, test_printf_25);
	tcase_add_test(tc_core, test_printf_26);
	tcase_add_test(tc_core, test_printf_27);
	tcase_add_test(tc_core, test_printf_28);
	tcase_add_test(tc_core, test_printf_29);
	tcase_add_test(tc_core, test_printf_30);
	tcase_add_test(tc_core, test_printf_31);
	tcase_add_test(tc_core, test_printf_32);
	tcase_add_test(tc_core, test_printf_33);
	tcase_add_test(tc_core, test_printf_34);
	tcase_add_test(tc_core, test_printf_35);
	tcase_add_test(tc_core, test_printf_36);
	tcase_add_test(tc_core, test_printf_37);
	tcase_add_test(tc_core, test_printf_38);
	tcase_add_test(tc_core, test_printf_39);
	suite_add_tcase(s, tc_core);

	return s;
}

int main()
{
	int number_failed = 0;
	SRunner *sr;
	sr = srunner_create(printf_suite());
	srunner_set_fork_status(sr, CK_NOFORK);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed != 0);
}

