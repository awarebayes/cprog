#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../inc/util.h"
#include "../inc/check_main.h"

int main()
{
    int number_failed = 0;
    SRunner *sr;
    sr = srunner_create(read_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    // srunner_add_suite(sr, read_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed != 0);
}