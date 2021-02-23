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

float find_cos_sign(float xa, float ya, float xb, float yb,
                    float xc, float yc)
{
    float vxa, vya;
    float vxb, vyb;

    vxa = xb - xa;
    vya = yb - ya;
    vxb = xc - xa;
    vyb = yc - ya;

    float result = roundf((vxa * vxb + vya * vyb) * 10000000000) / 10000000000;
    return result;
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

    printf("Input coordintaes of the first point: ");
    if ((input_result = input_two_float(&xa, &ya)) != 0)
    {
        printf("You have to enter two numbers");
        return 1;
    }
    printf("Input coordintaes of the second point: ");
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
    printf("Input coordintaes of the third point: ");
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

    type = find_cos_sign(xa, ya, xb, yb, xc, yc);
    type = min_float(type, find_cos_sign(xb, yb, xa, ya, xc, yc));
    type = min_float(type, find_cos_sign(xc, yc, xa, ya, xb, yb));

    if (type > 0)
        printf("0\n");
    else if (type < 0)
        printf("2\n");
    else
        printf("1\n");
    return 0;
}