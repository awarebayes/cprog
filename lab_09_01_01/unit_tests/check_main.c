#include <check.h>
#include "check_main.h"

int main()
{
    int number_failed = 0;
    SRunner *sr;
    sr = srunner_create(util_suite());
	srunner_add_suite(sr, movie_suite());
	srunner_add_suite(sr, movie_vector_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed != 0);
}