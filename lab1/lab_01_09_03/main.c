#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_EMPTY_SERIES 2


/* Функция, считающая математический ряд до первого ввода отрицательного аргумента. Принимает в себя результат, который в процессе будет изменен, возвращает код ошибки. */
int mathematic_series(double *result)
{
    int count = 0;
    double x, temp = 1;

    printf("Input argument: ");
    if (scanf("%lf", &x) != 1)
    {
        return ERR_IO;
    }

    if (x < 0)
    {
        return ERR_EMPTY_SERIES;
    }

    /* do while или пока не встретим отрицательный аргумент*/
    do
    {
        count++;
        temp *= count + x;

        if (scanf("%lf", &x) != 1)
        {
            return ERR_IO;
        }
    }
    while (x >= 0);

    *result = exp(1 / temp);

    return OK;
}

int mathematic_series(double *result);

int main(void)
{
    double g;
    int return_code;

    return_code = mathematic_series(&g);

    if (return_code == ERR_IO)
    {
        printf("Неверный ввод. Вводятся вещественные числа.");
        return ERR_IO;
    }
    else if (return_code == ERR_EMPTY_SERIES)
    {
        printf("Математический ряд не должен быть пустым");
        return ERR_EMPTY_SERIES;
    }

    printf("result: %lf", g);

    return OK;
}