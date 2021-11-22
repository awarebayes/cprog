#include "io.h"
#include "../inc/check_main.h"

START_TEST(test_read_1)
{
    FILE *f = fopen("./unit_tests/input/1.txt", "r");
    int ec = 0;
    int n = 0;
    int *res = read_numbers(f, &n, &ec);
    ck_assert_int_eq(ec, 3);
    ck_assert_int_eq(n, 0);
    ck_assert_ptr_null(res);
    fclose(f);
}
END_TEST

START_TEST(test_read_2)
{
    FILE *f = fopen("./unit_tests/input/2.txt", "r");
    int target[] = {1,2,3,4};
    int ec = 0;
    int n = 0;
    int *res = read_numbers(f, &n, &ec);
    ck_assert_int_eq(ec, 0);
    ck_assert_int_eq(n, 4);
    ck_assert_ptr_nonnull(res);
    ck_assert_mem_eq(res,target, sizeof(target));
    free(res);
}
END_TEST

Suite *read_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("read numbers");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_read_1);
    tcase_add_test(tc_core, test_read_2);
    suite_add_tcase(s, tc_core);

    return s;
}