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
    input = fopen(argv[1], "r");

    if (argc != 2)
        ec  = ARG_ERROR;
    if (!ec)
        min_max(input, &min, &max, &ec);
    if (!ec)
    {
        float mb = mean_between(input, min, max, &ec);
        printf("Mean between %f", mb);
    }
    fclose(input);
}

float mean_between(FILE *f, int min, int max, int *ec)
{
    fseek(f, 0, SEEK_SET);
    int n = 0;
    float sum = 0.0f;
    int el = 0;
    int started = 0;
    int ended = 0;
    float mean = 0;
    while (fscanf(f, "%d", &el))
    {
        if (el == max)
            ended = 1;
        if (started && !ended)
        {
            sum += el;
            n++;
        } 
        if (el == min)
            started = 1;
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
    fseek(f, 0, SEEK_SET);
    int first = 1;
    int el = 0;
    int read = 0;
    while(fscanf(f, "%d", &el))
    {
        if (first)
        {
            *min = *max = el;
            read = 1;
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