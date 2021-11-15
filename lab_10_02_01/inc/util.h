//
// Created by dev on 11/14/21.
//

#ifndef LAB_10_02_21_UTIL_H
#define LAB_10_02_21_UTIL_H

enum error_u
{
	ok,
	bad_malloc_err,
	input_err,
	input_array_overflow_err,
	bad_eval_err,
	negative_pow_err,
	zero_term_added_err,
	null_poly_err,
	bad_command_err,
};

void read_int_array(int *out, int *size, int max_size, char *in, int *ec);

int read_int(int *ec);

#endif //LAB_10_02_21_UTIL_H
