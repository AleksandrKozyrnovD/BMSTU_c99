#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define BITS (CHAR_BIT * sizeof(uint32_t))


/* Печать побитовая. Принимает беззнаковое целое 4-хбайтное число. Ничего не возвращает.*/
void bin_print(uint32_t a)
{
    for (int i = BITS - 1; i >= 0; i--)
    {
        printf("%u", (a >> i) & 1);
    }
    printf("\n");
}

/*Функция, изменяющая местами соседние четные и нечетные биты. Принимает указатель на беззнаковое 4-хбайтное число. Ничего не возвращает*/
void reshape_number(uint32_t *a)
{
    uint32_t mask1, mask2;
    uint32_t template_a = *a;
    for (uint32_t i = 0; i < BITS - 1;)
    {
        mask1 = template_a & 1;
        mask2 = (template_a >> 1) & 1;

        if (mask1)
        {
            mask1 <<= (i + 1);
            *a |= mask1;
        }
        else
        {
            mask1 = ~0 & ~(1 << (i + 1));
            *a &= mask1;
        }

        if (mask2)
        {
            mask2 <<= i;
            *a |= mask2;
        }
        else
        {
            mask2 = ~0 & ~(1 << i);
            *a &= mask2;
        }
        template_a = template_a >> 2;
        i = i + 2;
    }
}

void reshape_number(uint32_t *a);
void bin_print(uint32_t a);

int main(void)
{
    uint32_t a;
    printf("Input number a: ");
    if (scanf("%u", &a) != 1)
    {
        printf("Error: input must be an unsigned integer");
        return ERR_IO;
    }

    reshape_number(&a);
    printf("Result: ");
    bin_print(a);

    return OK;
}
