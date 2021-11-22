#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "../inc/util.h"
#include "../inc/io.h"

#define MEAN = 1

int means[] = { 100, 10, 3, 1 };
int thresholds[] = { 0, 100, 1000, 10000 };
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

size_t measure_time(sortf_t func, int size)
{
    int *arr = gen_arr(size);
    clock_t start = clock();
    func(arr, size, sizeof(int), int_cmp);
    clock_t end = clock();
    size_t ms = (end - start) * 1000000 / CLOCKS_PER_SEC;
    free(arr);
    return ms;
}

int64_t ticks(void)
{
    int32_t h, l;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (h), "=r" (l)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    int64_t t = ((int64_t)h << 32) | l;
    return t;
}

int64_t measure_ticks(sortf_t func, int size)
{
    int *arr = gen_arr(size);
    int64_t start = ticks();
    func(arr, size, sizeof(int), int_cmp);
    int64_t end = ticks();
    int64_t ms = (end - start);
    free(arr);
    return ms;
}

size_t measure_time_mean(sortf_t func, int size, int times)
{
    size_t sum = 0;
    // printf("%d, %d\n", size, times);
    for (int i = 0; i < times; i++)
    {
        size_t res = measure_time(func, size);
        // printf("profile %d %ld\n", i, res);
        sum += res;
    }
    // printf("sum %ld %ld\n", sum, sum / (size_t) times);
    return sum / (size_t)times;
}

size_t measure_ticks_mean(sortf_t func, int size, int times)
{
    size_t sum = 0;
    // printf("%d, %d\n", size, times);
    for (int i = 0; i < times; i++)
    {
        size_t res = measure_ticks(func, size);
        // printf("profile %d %ld\n", i, res);
        sum += res;
    }
    // printf("sum %ld %ld\n", sum, sum / (size_t) times);
    return sum / (size_t)times;
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
    int *sizes = malloc(sizeof(int) * (argc - 1));
    for (int i = 1; i < argc; i++)
        sscanf(argv[i], "%d", &sizes[i - 1]);

    printf("n,q,my\n");
    for (int i = 0; i < argc - 1; i++)
    {
        int n = sizes[i];
        size_t tqsort = measure_ticks_mean(qsort, n, find_mean(n));
        size_t tmysort = measure_ticks_mean(mysort, n, find_mean(n));
        printf("%d, %ld, %ld\n", sizes[i], tqsort, tmysort);
    }
    
    free(sizes);
    return 0;
}
