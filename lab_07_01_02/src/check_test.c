#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../inc/util.h"

START_TEST(test_key_1)
{
    int ab[] = {1, 2, 3, 4, 5};
    int n = sizeof(ab) / sizeof(int);
    int *ae = ab + n;

    int *pb_dst = NULL;
    int *pe_dst = NULL;
    int target_n = n;

    int target[] = {1,2,3,4,5};

    int ec = key(ab, ae, &pb_dst, &pe_dst);

    ck_assert_int_eq(ec, ok);
    ck_assert_ptr_nonnull(pb_dst);
    ck_assert_ptr_nonnull(pe_dst);
    ck_assert_int_eq(pe_dst - pb_dst, target_n);
    ck_assert_mem_eq(pb_dst, target, target_n);
    free(pb_dst);
}
END_TEST

START_TEST(test_key_2)
{
    int ab[] = {-1};
    int n = sizeof(ab) / sizeof(int);
    int *ae = ab + n;

    int *pb_dst = NULL;
    int *pe_dst = NULL;
    int target_n = 0;

    int ec = key(ab, ae, &pb_dst, &pe_dst);

    ck_assert_int_eq(ec, ok);
    ck_assert_ptr_null(pb_dst);
    ck_assert_ptr_null(pe_dst);
    ck_assert_int_eq(pe_dst - pb_dst, target_n);
    free(pb_dst);
}
END_TEST

START_TEST(test_key_3)
{
    int ab[] = {1,2,3,4,-1, 5, 6};
    int n = sizeof(ab) / sizeof(int);
    int *ae = ab + n;

    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int target[] = {1,2,3,4};
    int target_n = sizeof(target) / sizeof(int);

    int ec = key(ab, ae, &pb_dst, &pe_dst);

    ck_assert_int_eq(ec, ok);
    ck_assert_ptr_nonnull(pb_dst);
    ck_assert_ptr_nonnull(pe_dst);
    ck_assert_int_eq(pe_dst - pb_dst, target_n);
    ck_assert_mem_eq(pb_dst, target, target_n);
    free(pb_dst);
}
END_TEST

START_TEST(test_key_4)
{
    int ab[] = {1,2};

    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int ec = key(ab, ab-1, &pb_dst, &pe_dst);

    ck_assert_int_eq(ec, arg_err);
    ck_assert_ptr_null(pb_dst);
    ck_assert_ptr_null(pe_dst);
}
END_TEST

START_TEST(test_key_5)
{
    int ab[] = {1,2};

    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int ec = key(ab, NULL, &pb_dst, &pe_dst);

    ck_assert_int_eq(ec, arg_err);
    ck_assert_ptr_null(pb_dst);
    ck_assert_ptr_null(pe_dst);
}
END_TEST

START_TEST(test_key_6)
{
    int ab[] = {1,2};
    int n = sizeof(ab) / sizeof(int);
    int *ae = ab + n;

    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int ec = key(NULL, ae, &pb_dst, &pe_dst);

    ck_assert_int_eq(ec, arg_err);
    ck_assert_ptr_null(pb_dst);
    ck_assert_ptr_null(pe_dst);
}
END_TEST

START_TEST(test_mysort_1)
{
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    int n = sizeof(a) / sizeof(int);

    mysort(a, n, sizeof(int), int_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

START_TEST(test_mysort_2)
{
    int a[] = {3, 2, 1};
    int b[] = {1, 2, 3};
    int n = sizeof(a) / sizeof(int);

    mysort(a, n, sizeof(int), int_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

START_TEST(test_mysort_3)
{
    int a[] = {3, -2, 1};
    int b[] = {-2, 3, 3};
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
    int a[] = {3, 2, 1, -100};
    int b[] = {1, 2, 3, -100};
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
    double a[] = {3.0, 2.0, 1.0, -100.0};
    double b[] = {-100.0, 1.0, 2.0, 3.0};
    int n = sizeof(a) / sizeof(double);

    mysort(a, 3, sizeof(double), double_cmp);
    ck_assert_mem_eq(a, b, n);
}
END_TEST

Suite *test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Unit tests");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_key_1);
    tcase_add_test(tc_core, test_key_2);
    tcase_add_test(tc_core, test_key_3);
    tcase_add_test(tc_core, test_key_4);
    tcase_add_test(tc_core, test_key_5);
    tcase_add_test(tc_core, test_key_6);
    tcase_add_test(tc_core, test_mysort_1);
    tcase_add_test(tc_core, test_mysort_2);
    tcase_add_test(tc_core, test_mysort_3);
    tcase_add_test(tc_core, test_mysort_4);
    tcase_add_test(tc_core, test_mysort_5);
    tcase_add_test(tc_core, test_mysort_6);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int number_failed = 0;
    Suite *s;
    SRunner *sr;
    s = test_suite();
    sr = srunner_create(s);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed != 0);
}