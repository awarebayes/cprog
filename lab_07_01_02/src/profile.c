#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/util.h"

#define MEAN = 1

int means[] = {100, 10, 3, 1};
int thresholds[] = {0, 100, 1000, 10000};
int nmeans = 4;

int *gen_arr(int size)
{
    int *arr = malloc(size * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        int num = rand() % 1000;
        arr[i] = num;
    }
    return arr;
}

int measure_time(sortf_t func, int size)
{
    int *arr = gen_arr(size);
    clock_t start = clock();
    func(arr, size, sizeof(int), int_cmp);
    clock_t end = clock();
    int ms = (end-start) * 1000000 / CLOCKS_PER_SEC;
    free(arr);
    return ms;
}

int measure_time_mean(sortf_t func, int size, int times)
{
    long int sum = 0;
    for (int i = 0; i < times; i++)
    {
        sum += (long int)measure_time(func, size);
    }
    return (int)(sum / (long int)times);
}

int find_mean(int size)
{
    int mean = 1;
    for (int i = 0; i < nmeans; i++)
    {
        if (size >= thresholds[i])
            mean = means[i];
    }
    return mean;
}

int main(int argc, char **argv)
{
    int *sizes = malloc(sizeof(int) * (argc-1));
    for (int i = 1; i < argc; i++)
        sscanf(argv[i], "%d", &sizes[i-1]);

    printf("n,q,my\n");
    for (int i = 0; i < argc-1; i++)
    {
        int n = sizes[i];
        int tqsort = measure_time_mean(qsort, n, find_mean(n));
        int tmysort = measure_time_mean(mysort, n, find_mean(n));
        printf("%d, %d, %d\n", sizes[i], tqsort, tmysort);
    }
    
    free(sizes);
    return 0;
}
