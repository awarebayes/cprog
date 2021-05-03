#include "count.h"
#include <string.h>
#include <stdio.h>

void print_word_count(char **pa, int n_words)
{
    int count = 0;
    int encountered = 0;

    printf("Result: \n");
    for (int i = 0; i < n_words; i++)
    {
        encountered = 0;
        for (int j = 0; j < i; j++)
            if (strcmp(pa[i], pa[j]) == 0)
                encountered = 1;

        if (!encountered)
        {
            count = 0;
            for (int j = i; j < n_words; j++)
                if (strcmp(pa[i], pa[j]) == 0)
                    count++;
            printf("%s %d\n", pa[i], count);
        } 
    }
}