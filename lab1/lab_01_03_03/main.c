#include <stdio.h>

int main()
{
    float velocity_0, acceleration, time, s;
    printf("Input speed, acceleration and time: ");
    scanf("%f%f%f", &velocity_0, &acceleration, &time);
    
    s = velocity_0 * time + (acceleration * time * time) / 2.0;
    printf("%f", s);

    return 0;
}