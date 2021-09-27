#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/util.h"

int *gen_arr(int size)
{
    int *arr = malloc(size*sizeof(int));
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

int main()
{
    int sizes[] = {10, 100, 1000, 10000, 100000};
    printf("n, q, my\n");
    for (size_t i = 0; i < sizeof(sizes)/sizeof(int); i++)
    {
        int n = sizes[i];
        int tqsort = measure_time(qsort, n);
        int tmysort = measure_time(mysort, n);
        printf("%d, %d, %d\n", sizes[i], tqsort, tmysort);
    }
    
    return 0;
}
