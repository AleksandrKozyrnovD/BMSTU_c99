#include <stdio.h>
#include <math.h>

#define TO_RADIAN (3.141592 / 180.0)

int main()
{
    float side1, side2, phi, s;

    printf("Input a and b and phi (degrees): ");
    scanf("%f%f%f", &side1, &side2, &phi);

    s = 0.5 * side1 * side2 * sin(phi * TO_RADIAN);
    printf("area of a triangle = %f\n", s);

    return 0;
}