#include <stdio.h>

#define NO_POSITIVE -1

int process(FILE *f, int *result);

int main()
{
    int result;
    int rc = process(stdin, &result);
    printf("%d %d \n", rc, result);

}

int process(FILE *f, int *result)
{
    int flag = 1;
    int prev_neg = 0;
    int max_pos = -1;
    int cur = 0;
    int ret = 0;
    while (flag)
    {
        if (fscanf(f, "%d", &cur) != 1)
            flag = 0;
        else
        {
            if (cur < 0)
                prev_neg = 1;
            else if (cur > 0)
            {
                if (prev_neg && cur > max_pos)
                    max_pos = cur;
                prev_neg = 0;
            }
        }
    }

    if (max_pos > 1)
        *result = max_pos;
    else
        ret = NO_POSITIVE;
    return ret;
}