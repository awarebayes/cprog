#include <stdio.h>
#include <math.h>
 
int input_two_double(double *a, double *b)
{
int rc = 0;
rc = scanf("%lf %lf", a, b);
if (rc != 2)
return 1;
else
return 0;
}
 
int check_if_equal(double xa, double ya, double xb, double yb)
{
if (fabs(xa - xb) < 1e-8 && fabs(ya - yb) < 1e-8)
return 1;
return 0;
}
 
int check_if_on_line(double xa, double ya, double xb, double yb,
double xc, double yc)
{
if (fabs((xc - xa) * (yb - ya) - (xb - xa) * (yc - ya)) < 1e-8)
return 1;
return 0;
}
 
double find_cos_sign(double xa, double ya, double xb, double yb,
double xc, double yc)
{
double vxa, vya;
double vxb, vyb;
 
vxa = xb - xa;
vya = yb - ya;
vxb = xc - xa;
vyb = yc - ya;
 
double result = round((vxa * vxb + vya * vyb) * 10000000000) / 10000000000;
return result;
}
 
double min_double(double num1, double num2)
{
if (num1 < num2)
return num1;
else
return num2;
}
 
int main(void)
{
double xa, ya;
double xb, yb;
double xc, yc;
double type;
 
int input_result;
 
printf("Input coordintaes of the first point: ");
if ((input_result = input_two_double(&xa, &ya)) != 0)
{
printf("You have to enter two numbers");
return 1;
}
printf("Input coordintaes of the second point: ");
if ((input_result = input_two_double(&xb, &yb)) != 0)
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
if ((input_result = input_two_double(&xc, &yc)) != 0)
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
type = min_double(type, find_cos_sign(xb, yb, xa, ya, xc, yc));
type = min_double(type, find_cos_sign(xc, yc, xa, ya, xb, yb));
 
if (type > 0)
printf("0");
else if (type < 0)
printf("2");
else
printf("1");
return 0;
}