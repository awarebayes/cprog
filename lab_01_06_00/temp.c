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

int main(void)
{
    float xa, ya;
    float xb, yb;
    float xc, yc;
    float type;

    if (!input_two_floats(&xa, &ya))
        goto input_error;
    if (!input_two_floats(&xb, &yb))
        goto input_error;
    if (same_points(xa, ya, xb, yb))
        goto same_points_error;
    if (!input_two_floats(&xc, &yc))
        goto input_error;
    if (same_points(xa, ya, xc, yc) ||
        same_points(xc, yc, xb, yb))
        goto same_points_error;
    if (check_line(xb, yb, xa, ya, xc, yc))
    {
        printf("This is a line");
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

    // Errors
    
    same_points_error:
        printf("Same points");
    return 1;
    input_error:
        printf("Input Error");
    return 1;
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