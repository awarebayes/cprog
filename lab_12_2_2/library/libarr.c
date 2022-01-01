#include "libarr.h"
#include <stdlib.h>

void arr_fib(int *arr, int n)
{
    int fib_n_m_1 = 0;
    int fib_n_m_2 = 1;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            arr[i] = fib_n_m_1;
        else if (i == 1)
            arr[i] = fib_n_m_2;
        else
        {
            int new_fib = fib_n_m_1 + fib_n_m_2;
            fib_n_m_1 = fib_n_m_2;
            fib_n_m_2 = new_fib;
            arr[i] = new_fib;
        }
    }
}

int entries(int *haystacks, int n_hs, int *needles, int *n_needles)
{
    int n_set = 0;
    int init_needles = *n_needles;
    *n_needles = 0;
    int *set = malloc(n_hs);
    int out_of_needles = 0;
    for (int i = 0; i < n_hs; i++)
    {
        int found = 0;
        for (int j = 0; j < n_set && !found; j++)
        {
            if (haystacks[i] == set[j])
                found = 1;
        }
        if (!found)
        {
	        set[n_set++] = haystacks[i];
			if (*n_needles < init_needles)
	        {
		        needles[*n_needles] = i;
	            *n_needles += 1;
			}
			else
				out_of_needles = 1;
        }
    }
	*n_needles = n_set;
    free(set);
    return out_of_needles;
}