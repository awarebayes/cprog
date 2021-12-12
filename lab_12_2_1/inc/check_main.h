#ifndef __CHECK_MAIN_H__
#define __CHECK_MAIN_H__

#include "util.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *key_suite(void);
Suite *mysort_suite(void);
Suite *n_word_suite(void);
Suite *read_suite(void);

#endif /* CHECK */