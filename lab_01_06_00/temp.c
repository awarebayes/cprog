#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int input_two_float(float *a, float *b)
{
    return (scanf("%f %f", a, b) != 2);
}


/*
 * is value x close to target
 */
bool is_close(const float x, const float target)
{
    return fabs(x - target) < 10e-5;
}

float vec_dot(float a_x, float a_y, float b_x,
              float b_y, float c_x, float c_y)
{
    float ba_x, ba_y, bc_x, bc_y;
    float dot; ///< dot product
    ba_x = a_x - b_x;
    ba_y = a_y - b_y;
    bc_x = c_x - b_x;
    bc_y = c_y - b_y;

    dot = (ba_x * bc_x) + (ba_y * bc_y);
    if (is_close(dot, 0))
        return 0;
    return dot;
}

float min_float(float num1, float num2)
{
    if (num1 < num2)
        return num1;
    else
        return num2;
}

int main(void)
{
    float xa, ya;
    float xb, yb;
    float xc, yc;
    float type;

    if (scanf("%f %f", &xa, &ya) != 2 ||
        scanf("%f %f", &xb, &yb) != 2 ||
        scanf("%f %f", &xc, &yc) != 2)
    {
        printf("Input Error\n");
        return 1;
    }


    type = vec_dot(xa, ya, xb, yb, xc, yc);
    type = min_float(type, vec_dot(xb, yb, xa, ya, xc, yc));
    type = min_float(type, vec_dot(xc, yc, xa, ya, xb, yb));

    if (type > 0)
        printf("0\n");
    else if (type < 0)
        printf("2\n");
    else
        printf("1\n");
    return 0;
}