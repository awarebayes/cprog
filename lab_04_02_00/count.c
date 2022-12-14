#include "count.h"
#include "split.h"
#include <string.h>
#include <stdio.h>

void unique_words(char **pa, char **unique, int n_words, int *n_unique)
{
    int encountered = 0;
    *n_unique = 0;
    for (int i = 0; i < n_words; i++)
    {
        encountered = 0;
        for (int j = 0; j < i; j++)
            if (strcmp(pa[i], pa[j]) == 0)
                encountered = 1;

        if (!encountered)
        {
            strcpy(unique[*n_unique], pa[i]);
            *n_unique += 1;
        } 
    }
}

void word_count(char **pa, char **unique, int *count, int n_words, int n_unique)
{
    for (int i = 0; i < n_unique; i++)
    {
        for (int j = 0; j < n_words; j++)
            if (strcmp(unique[i], pa[j]) == 0)
                count[i] += 1;
    }
}

void print_word_count(int n_unique, char **unique, int *count)
{
    printf("Result: \n");
    for (int i = 0; i < n_unique; i++)
    {
        printf("%s %d\n", unique[i], count[i]);
    }
}