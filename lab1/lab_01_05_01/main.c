#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2


/* Функция, которая принимает делимое и делитель, меняет значения частного и остатка. Ничего не возвращает. */
void quotient_remainder(int dividend, int denominator, int *quotient, int *remainder)
{
    *quotient = 0;
    while (dividend >= denominator)
    {
        dividend = dividend - denominator;
        *quotient = *quotient + 1;
    }
    *remainder = dividend;
}

void quotient_remainder(int dividend, int denominator, int *quotient, int *remainder);

int main()
{
    int a, d;
    int q;
    int r;

    printf("Input int a and int d: ");
    if (scanf("%d%d", &a, &d) != 2)
    {
        printf("Input error");
        return ERR_IO;
    }

    if (a <= 0 || d <= 0)
    {
        printf("Range error");
        return ERR_RANGE;
    }

    quotient_remainder(a, d, &q, &r);
    printf("%d %d", q, r);

    return OK;
}