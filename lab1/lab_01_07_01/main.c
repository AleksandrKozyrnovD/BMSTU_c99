#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/* Синус, расписанный по ряду Маклорена. Принимает аргумент и точность вычислений, возвращает результат.*/
double s_func(double x, double eps)
{
    double s, current;
    int n;
    s = 0;
    current = x;
    n = 1;
    while (fabs(current) >= eps) 
    {
        s += current;
        current = -current * ((x * x) / ((2 * n) * (2 * n + 1)));
        n++;
    }
    return s;
}

double s_func(double x, double eps);

int main(void)
{
    double x, eps, delta_absolute, delta_relative, f, s;

    printf("Input argument and epsilon: ");
    if (scanf("%lf%lf", &x, &eps) != 2)
    {
        printf("Input error");
        return ERR_IO;
    }

    if (eps <= 0 || eps > 1)
    {
        printf("Input error");
        return ERR_RANGE;
    }
    
    f = sin(x);
    s = s_func(x, eps);
    
    delta_absolute = fabs(f - s);
    delta_relative = delta_absolute / fabs(f);
    printf("%.6lf %.6lf %.6lf %.6lf\n", s, f, delta_absolute, delta_relative);

    return OK;
}