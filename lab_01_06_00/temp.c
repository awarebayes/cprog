#include <stdio.h>
#include <math.h>

int input_two_float(float *a, float *b)
{
    return (scanf("%f %f", a, b) != 2);
}

int check_if_equal(float xa, float ya, float xb, float yb)
{
    if (fabs(xa - xb) < 1e-8 && fabs(ya - yb) < 1e-8)
        return 1;
    return 0;
}

int check_if_on_line(float xa, float ya, float xb, float yb,
                     float xc, float yc)
{
    if (fabs((xc - xa) * (yb - ya) - (xb - xa) * (yc - ya)) < 1e-8)
        return 1;
    return 0;
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

    int input_result;

    if ((input_result = input_two_float(&xa, &ya)) != 0)
    {
        printf("You have to enter two numbers");
        return 1;
    }
    if ((input_result = input_two_float(&xb, &yb)) != 0)
    {
        printf("You have to enter two numbers");
        return 1;
    }
    input_result = check_if_equal(xa, ya, xb, yb);
    if (input_result != 0)
    {
        printf("There must be three different points");
        return 1;
    }
    if ((input_result = input_two_float(&xc, &yc)) != 0)
    {
        printf("You have to enter two numbers");
        return 1;
    }
    input_result = check_if_equal(xa, ya, xc, yc);
    if (input_result != 0)
    {
        printf("There must be three different points");
        return 1;
    }
    input_result = check_if_equal(xc, yc, xb, yb);
    if (input_result != 0)
    {
        printf("There must be three different points");
        return 1;
    }
    input_result = check_if_on_line(xb, yb, xa, ya, xc, yc);
    if (input_result != 0)
    {
        printf("The points must not be on the same line");
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