#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR 3
#define ZERO 0.000001

/* Функция, считающая длину отрезка по координатам начала и конца. Принимает координаты двух вершин, возвращает значение длины отрезка*/
double line_lenght(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


/* Функция, считающая площадь треугольника по координатам его вершин. Принимает координаты трех вершин, меняет значение площади. Возвращает код ошибки, показывающий наличие ошибки (если она случалась)*/
int area_of_triangle(double x1, double y1, double x2, double y2, double x3, double y3, double *square)
{
    double line1, line2, line3, perimeter;
    line1 = line_lenght(x1, y1, x2, y2);
    line2 = line_lenght(x1, y1, x3, y3);
    line3 = line_lenght(x3, y3, x2, y2);
    
    if (line1 < ZERO || line2 < ZERO || line3 < ZERO)
    {
        return ERR_RANGE;
    }

    perimeter = (line1 + line2 + line3) / 2.0;
    *square = sqrt(perimeter * (perimeter - line1) * (perimeter - line2) * (perimeter - line3));

    if (*square < ZERO)
    {
        return ERR;
    }

    return OK;
}


double line_lenght(double x1, double y1, double x2, double y2);
int area_of_triangle(double x1, double y1, double x2, double y2, double x3, double y3, double *square);

int main(void)
{
    double x1, y1, x2, y2, x3, y3, square;
    int return_code;

    printf("Input three points: ");
    if (scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3) != 6)
    {
        return ERR_IO;
    }

    return_code = area_of_triangle(x1, y1, x2, y2, x3, y3, &square);
    if (return_code == ERR_RANGE)
    {
        printf("Sides must be bigger than zero");
        return return_code;
    }
    else if (return_code == ERR)
    {
        printf("Two or more sides must not be parallel");
        return return_code;
    }
    
    printf("%.6lf", square);

    return OK;
}
