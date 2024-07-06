#include <stdio.h>

int main(void)
{
    int num, multiplication;

    printf("Input three-digit number: ");
    scanf("%d", &num);

    if (num < 0)
    {
        num = -num;
    }

    multiplication = (num % 10) * ((num / 10) % 10) * ((num / 100) % 10);

    printf("%d", multiplication);

    return 0;
}