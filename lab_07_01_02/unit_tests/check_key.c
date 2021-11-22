#include "../inc/util.h"
#include "../inc/check_main.h"

START_TEST(test_key_1)
{
    int ab[] = { 1, 2, 3, 4, 5 };
    int n = sizeof(ab) / sizeof(int);
    int *ae = ab + n;

    int *pb_dst = NULL;
    int *pe_dst = NULL;
    int target_n = n;

    int target[] = { 1, 2, 3, 4, 5 };

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
    int ab[] = { 1, 2, 3, 4, -1, 5, 6 };
    int n = sizeof(ab) / sizeof(int);
    int *ae = ab + n;

    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int target[] = { 1, 2, 3, 4 };
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
    int ab[] = { 1, 2 };

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
    int ab[] = { 1, 2 };

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
    int ab[] = { 1, 2 };
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

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("key");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_key_1);
    tcase_add_test(tc_core, test_key_2);
    tcase_add_test(tc_core, test_key_3);
    tcase_add_test(tc_core, test_key_4);
    tcase_add_test(tc_core, test_key_5);
    tcase_add_test(tc_core, test_key_6);
    suite_add_tcase(s, tc_core);

    return s;
}