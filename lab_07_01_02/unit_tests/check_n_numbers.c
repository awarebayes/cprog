#include "io.h"
#include "../inc/check_main.h"

START_TEST(test_n_1)
{
    FILE *f = fopen("./unit_tests/input/1.txt", "r");
    ck_assert_ptr_nonnull(f);
    int target_res = 0;
    int ec = 0;
    int res = file_n_numbers(f, &ec);
    ck_assert_int_eq(ec, 2);
    ck_assert_int_eq(res, target_res);
    fclose(f);
}
END_TEST

START_TEST(test_n_2)
{
    FILE *f = fopen("./unit_tests/input/2.txt", "r");
    ck_assert_ptr_nonnull(f);
    int target_res = 4;
    int ec = 0;
    int res = file_n_numbers(f, &ec);
    ck_assert_int_eq(ec, 0);
    ck_assert_int_eq(res, target_res);
    fclose(f);
}
END_TEST

Suite *n_word_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("n numbers");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_n_1);
    tcase_add_test(tc_core, test_n_2);
    suite_add_tcase(s, tc_core);

    return s;
}