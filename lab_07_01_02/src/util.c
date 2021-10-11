#include "../inc/util.h"

#include <stdlib.h>
#include <string.h>

/*
 * 2.
 * В массиве остаются элементы от нулевого до m-го, где m - индекс первого отри-
 * цательного элемента этого массива либо число n (размер исходного массива), если
 * такого элемента в массиве нет. Т.е. отфильтрованный массив содержит элементы,
 * расположенные перед первым отрицательным элементом, или весь исходный мас-
 * сив, если отрицательные элементы отсутствуют.
*/

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int ec = ok;
    if (pb_src == NULL || pe_src == NULL)
        ec = arg_err;
    if (pe_src < pb_src)
        ec = arg_err;
    if (ec)
        return ec;

    const int *p_neg = pe_src;
    const int *p_cur_src = pb_src;
    int flag = 1;
    while (p_cur_src < pe_src && flag)
    {
        if (*p_cur_src < 0)
        {
            p_neg = p_cur_src;
            flag = 0;
        }
        else
            p_cur_src++;
    }

    int pos_count = p_cur_src - pb_src;
    if (pos_count != 0)
    {
        *pb_dst = malloc(sizeof(int) * pos_count);
        if (*pb_dst == NULL)
            ec = malloc_err;
    }
    if (!ec && pos_count != 0)
    {
        *pe_dst = *pb_dst + pos_count;
        p_cur_src = pb_src;
        int *p_cur_dst = *pb_dst;
        while (p_cur_src < p_neg)
        {
            *(p_cur_dst++) = *(p_cur_src++);
        }
    }

    return ec;
}

void memswap(void *v1, void *v2, size_t size)
{
    void *temp = malloc(size);
    if (temp != NULL)
    {
        memcpy(temp, v1, size);
        memcpy(v1, v2, size);
        memcpy(v2, temp, size);
        free(temp);
    }
}

// Сортировка выбором
void mysort(void *base, size_t nitems, size_t size, int (*cmp)(const void*, const void*))
{
    char *cbase = base;
    for (int j = nitems - 1; j > 0; j--)
    {
        // find max
        char *max = cbase;
        for (int i = 0; i <= j; i++)
        {
            void *el = cbase + i * size;
            if (cmp(el, max) > 0)
                max = el;
        }
        //printf("swapping %d %d\pos_count", (max-base)/sizeof(int), j);
        memswap(max, cbase + size * j, size);
    }
}

int int_cmp(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

