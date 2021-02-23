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

#define M_PI 4.0 * atanf(1.0)
#define DEG_90 M_PI / 2.0f

float vec_len(float a_x, float a_y);
int vec_cos_sign(float a_x, float a_y, float b_x, float b_y,
float c_x, float c_y);
bool is_close(const float x, const float target);

// float to_deg(float rad){ return rad * 180 / M_PI; }   

int main()
{
    ///< Points
    float ax, ay; 
    float bx, by;
    float cx, cy;
    float angle_a, angle_b, angle_c;

    printf("ax, ay:\n");
    if (scanf("%f %f", &ax, &ay) != 2 ||
        scanf("%f %f", &bx, &by) != 2 ||
        scanf("%f %f", &cx, &cy) != 2)
    {
        printf("Input Error\n");
        return 1;
    }

    angle_a = vec_cos_sign(bx, by, ax, ay, cx, cy);
    angle_b = vec_cos_sign(ax, ay, bx, by, cx, cy);
    angle_c = vec_cos_sign(ax, ay, cx, cy, bx, by);

    //printf("a %f b %f c %f", to_deg(angle_a), to_deg(angle_b), to_deg(angle_c));    
    if (angle_a > 0 && angle_b > 0 && angle_c > 0)
    {
        printf("0\n");
    }
    else if (is_close(angle_a, 0) || 
             is_close(angle_b, 0) ||
             is_close(angle_c, 0))
    {
        printf("1\n");
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
 * Sign of Float
 * if close to 0 = 0
 * else = 
 */
int sign(float f)
{
    if(is_close(f, 0))
        return 0;
    return (f > 0) ? 1 : -1;
}

/*
 * sign of cosine between two vectors of points
 * @param *_* - vector's x/y component
 * @return Angle between two vectors: ab and bc
 */
int vec_cos_sign(float a_x, float a_y, float b_x,
float b_y, float c_x, float c_y)
{
    float ba_x, ba_y, bc_x, bc_y; /**< vectors ab, bc */
    float dot; ///< dot product
    ba_x = a_x - b_x;
    ba_y = a_y - b_y; 
    bc_x = c_x - b_x;
    bc_y = c_y - b_y;

    dot = (ba_x * bc_x) + (ba_y * bc_y); 
    return sign(dot);
}