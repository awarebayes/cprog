//
// Created by dev on 11/14/21.
//

#ifndef LAB_10_02_21_UTIL_H
#define LAB_10_02_21_UTIL_H

enum error_u
{
	ok,
	bad_malloc_err,
	input_error,
};

void read_int_array(int *out, char *in);

#endif //LAB_10_02_21_UTIL_H
