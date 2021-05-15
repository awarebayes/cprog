/*
 * 4. найти среднее значение чисел, расположенных между минимальным и максималь-
 * ным числами («между» - не по значению, а по расположению); предполагается, что
 */
#include <stdio.h>

#define EMPTY_FILE -1
#define NO_BETWEEN -2
#define ARG_ERROR -3

void min_max(FILE *f, int *min, int *max, int *ec);
float mean_between(FILE *f, int min, int max, int *ec);

int main(int argc, char **argv)
{
    FILE *input;
    int ec = 0;
    int min, max;
    float mb = 0;
    input = fopen(argv[1], "r");

    if (argc != 2)
        ec  = ARG_ERROR;
    if (!ec)
        min_max(input, &min, &max, &ec);
    if (!ec)
        mb = mean_between(input, min, max, &ec);
    if (!ec)
        printf("%f\n", mb);
    fclose(input);
    return ec;
}

float mean_between(FILE *f, int min, int max, int *ec)
{
    rewind(f);
    int n = 0;
    float sum = 0.0f;
    int el = 0;
    int started = 0;
    int ended = 0;
    float mean = 0;
    int should_continue = 0;
    while (!feof(f))
    {
        fscanf(f, "%d", &el);
        should_continue = 0;
        if ((el == max || el == min) && !started)
        {
            started = 1;
            should_continue = 1;
        }
        if ((el == max || el == min) && started && !should_continue)
        {
            ended = 1;
            should_continue = 1;
        }
        if (started && !ended && !should_continue)
        {
            sum += el;
            n++;
            should_continue = 0;
        } 
    }
    if (n == 0)
    {
        *ec = NO_BETWEEN;
        mean = 0;
    }
    else 
        mean = sum / (float)n;
    return mean;
}

void min_max(FILE *f, int *min, int *max, int *ec)
{
    rewind(f);
    int first = 1;
    int el = 0;
    int read = 0;
    while(!feof(f))
    {
        fscanf(f, "%d", &el);
        if (first)
        {
            *min = *max = el;
            read = 1;
            first = 0;
        }
        else
        {
            if (el > *max)
                *max = el;
            if (el < *min)
                *min = el;
        }
    }
    if (!read)
        *ec = EMPTY_FILE;
}