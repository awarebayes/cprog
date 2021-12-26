#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

int main(int argc, char **argv)
{
	FILE *fin = fopen(argv[1], "r");
	int n_iter = atoi(argv[2]);
	int ended = 0;
	matrix_t old_state = matrix_read(fin);
	matrix_t new_state = old_state;
	printf("0\n");
	matrix_print(&old_state, stdout);

	for (int i = 1; ((i <= n_iter) || n_iter < 0) && !ended ; i++)
	{
		printf("Step: %d\n", i);
		new_state = life_update(&old_state, &ended);
		matrix_print(&new_state, stdout);
		matrix_delete(&old_state);
		old_state = new_state;
	}
	if (ended)
		printf("Ended! :(\n");
	
	matrix_delete(&new_state);
	fclose(fin);
}
