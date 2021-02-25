/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 6 лабораторной 1.
 * Принять с клавиатуры координаты 𝑥𝑎, 𝑦𝑎, . . . , 𝑦𝑐 треугольника 𝑎𝑏𝑐 на плоскости.
 * Определить тип треугольника и вывести на экран целое число в зависимости от
 * ответа: 0 — остроугольный, 1 — прямоугольный, 2 — тупоугольный
 * gcc -std=c99 -Werror -Wall -lm ./lab_01_06_00/main.c -o ./bin/lab6 && ./bin/lab6
 */


#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool same_points(float xa, float ya, float xb, float yb);
bool check_line(float xa, float ya, float xb, float yb,
float xc, float yc);

float min_float(float num1, float num2);
float vec_dot(float a_x, float a_y, float b_x,
float b_y, float c_x, float c_y);
bool is_close(const float x, const float target);
bool input_two_floats(float *a, float *b);
int input(int* xa, int* ya, int* xb, int* yb, int* xc, int* yc);
void print_error(int error_flag);

int main(void)
{
    float xa, ya;
    float xb, yb;
    float xc, yc;
    float type;
    int error_flag = 0;

    error_flag = input(&xa, &ya, &xb, &yb, &xc, &yc);

    if (!error_flag)
    {
        type = vec_dot(xa, ya, xb, yb, xc, yc);
        type = min_float(type, vec_dot(xb, yb, xa, ya, xc, yc));
        type = min_float(type, vec_dot(xc, yc, xa, ya, xb, yb));

        if (type > 0)
            printf("0\n");
        else if (type < 0)
            printf("2\n");
        else
            printf("1\n");
    }

    return error_flag;
}

/*
 * Check whether points are the same
 */
bool same_points(float xa, float ya, float xb, float yb)
{
    return (is_close(xa, xb) && is_close(ya, yb));
}

/*
 * Check whether 3 points are on the same line 
 */
bool check_line(float xa, float ya, float xb, float yb,
float xc, float yc)
{
    return is_close(((xc - xa) * (yb - ya) - (xb - xa) * (yc - ya)), 0);
}

float min_float(float num1, float num2)
{
    if (num1 < num2)
        return num1;
    else
        return num2;
}

/*
 * sign of cosine between two vectors of points
 * @param *_* - vector's x/y component
 * @return Angle between two vectors: ab and bc
 */

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
/*
 * is value x close to target
 */
bool is_close(const float x, const float target)
{
    return fabs(x - target) < 10e-5;
}

bool input_two_floats(float *a, float *b)
{
    return scanf("%f %f", a, b) == 2;
}

void print_error(int error_flag)
{
    switch (error_flag)
    {
        case 1:
            printf("Input Error\n");
            break;
        case 2:
            printf("Same Points\n");
            break;
        case 3:
            printf("On line\n");
            break;
        default:
            break;
    }
}

int input(int* xa, int* ya, int* xb, int* yb, int* xc, int* yc)
{
    int error_flag = 0;
    if (!input_two_floats(xa, ya))
        error_flag = 1;
    else if (!input_two_floats(xb, yb))
        error_flag = 1;
    else if (same_points(*xa, *ya, *xb, *yb))
        error_flag = 2;
    else if (!input_two_floats(xc, yc))
        error_flag = 1;
    else if (same_points(*xa, *ya, *xc, *yc) ||
        same_points(*xc, *yc, *xb, *yb))
        error_flag = 2;
    else if (check_line(*xb, *yb, *xa, *ya, *xc, *yc))
        error_flag = 3;
    return error_flag;
}
