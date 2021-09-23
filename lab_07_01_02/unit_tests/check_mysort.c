#include "../inc/util.h"
#include "../inc/check_main.h"

START_TEST(test_mysort_1)
{
    int a[] = { 1, 2, 3 };
    int b[] = { 1, 2, 3 };
    int n = sizeof(a) / sizeof(int);

    mysort(a, n, sizeof(int), int_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

START_TEST(test_mysort_2)
{
    int a[] = { 3, 2, 1 };
    int b[] = { 1, 2, 3 };
    int n = sizeof(a) / sizeof(int);

    mysort(a, n, sizeof(int), int_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

START_TEST(test_mysort_3)
{
    int a[] = { 3, -2, 1 };
    int b[] = { -2, 3, 3 };
    int n = sizeof(a) / sizeof(int);

    mysort(a, n, sizeof(int), int_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

START_TEST(test_mysort_4)
{
    int a[] = {-2, 3, 1};
    int b[] = {-2, 3, 1};
    int n = sizeof(a) / sizeof(int);

    mysort(a, 0, sizeof(int), int_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

START_TEST(test_mysort_5)
{
    int a[] = { 3, 2, 1, -100 };
    int b[] = { 1, 2, 3, -100 };
    int n = sizeof(a) / sizeof(int);

    mysort(a, 3, sizeof(int), int_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

int double_cmp(const void * a, const void * b)
{
   return ( *(double*)a - *(double*)b ) > 0;
}

START_TEST(test_mysort_6)
{
    double a[] = { 3.0, 2.0, 1.0, -100.0 };
    double b[] = { -100.0, 1.0, 2.0, 3.0 };
    int n = sizeof(a) / sizeof(double);

    mysort(a, 3, sizeof(double), double_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

Suite *mysort_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("mysort");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_mysort_1);
    tcase_add_test(tc_core, test_mysort_2);
    tcase_add_test(tc_core, test_mysort_3);
    tcase_add_test(tc_core, test_mysort_4);
    tcase_add_test(tc_core, test_mysort_5);
    tcase_add_test(tc_core, test_mysort_6);
    suite_add_tcase(s, tc_core);

    return s;
}