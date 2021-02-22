/*
 * Написал Щербина Михаил ИУ7-15Б.
 * Задача 6 лабораторной 1.
 * Принять с клавиатуры координаты 𝑥𝑎, 𝑦𝑎, . . . , 𝑦𝑐 треугольника 𝑎𝑏𝑐 на плоскости.
 * Определить тип треугольника и вывести на экран целое число в зависимости от
 * ответа: 0 — остроугольный, 1 — прямоугольный, 2 — тупоугольный
 * gcc -std=c99 -Werror -Wall -lm ./lab01_06_24/main.c -o ./bin/lab6 && ./bin/lab6
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define M_PI 3.141593
#define DEG_90 M_PI/2.0

float vec_len(float a_x, float a_y);
float vec_angle(float a_x, float a_y,
                float b_x, float b_y,
                float c_x, float c_y);
bool is_close(const float x, const float target);

int main()
{
    float ax, ay; // points
    float bx, by;
    float cx, cy;

    printf("ax, ay:\n");
    if (scanf("%f %f", &ax, &ay) != 2)
        return 1;
    if (scanf("%f %f", &bx, &by) != 2)
        return 1;
    if (scanf("%f %f", &cx, &cy) != 2)
        return 1;

    float angle_a, angle_b, angle_c;
    angle_a = vec_angle(bx, by, ax, ay, cx, cy);
    angle_b = vec_angle(ax, ay, bx, by, cx, cy);
    angle_c = vec_angle(ax, ay, cx, cy, bx, by);

    if(is_close(angle_a, DEG_90) || is_close(angle_b, DEG_90) || is_close(angle_c, DEG_90))
    {
        printf("1\n");
    } 
    else if(angle_a < DEG_90 && angle_b < DEG_90 && angle_c < DEG_90)
    {
        printf("0\n");
    }
    else
    {
        printf("2\n");
    }

    return 0;
}

/*
 * is value x close to target
 */
bool is_close(const float x, const float target)
{
    return fabs(x - target) < 10e-5;
}

/*
 * Length of vector
 * @param a_x x component
 * @param a_y y component
 * @return vector length 
 */
float vec_len(const float a_x, const float a_y)
{
    return sqrt(a_x*a_x + a_y*a_y);
}

/*
 * angle between vectors on points
 * @param *_* - vector's x/y component
 * @return Angle between two vectors: ab and bc
 */
float vec_angle(float a_x, float a_y,
                float b_x, float b_y,
                float c_x, float c_y)
{
    float ba_x, ba_y, bc_x, bc_y; /**< vectors ab, bc */
    float len_ba, len_bc; ///< lengths of vectors
    ba_x = a_x - b_x;
    ba_y = a_y - b_y; 
    bc_x = c_x - b_x;
    bc_y = c_y - b_y;

    len_ba = vec_len(ba_x, ba_y);
    len_bc = vec_len(bc_x, bc_y);

    ///< by defenition angle between _ and 0 is 0
    if (is_close(len_ba, 0) || is_close(len_bc, 0))
    {
        return 0;
    }

    float dot = (ba_x * bc_x) + (ba_y * bc_y); ///< dot product
    return acos(dot / (len_ba * len_bc));
}