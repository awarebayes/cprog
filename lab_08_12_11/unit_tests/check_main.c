#include <check.h>
#include "../inc/check_main.h"

int main()
{
    int number_failed = 0;
    SRunner *sr;
    sr = srunner_create(read_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_add_suite(sr, matrix_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed != 0);
}