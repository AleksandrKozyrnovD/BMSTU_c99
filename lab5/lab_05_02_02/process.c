#include <stdio.h>
#include "process.h"

int get_average(FILE *file, double *average)
{
    double number;
    int count = 0;
    *average = 0.0;
    if (fseek(file, 0, SEEK_SET) != 0)
        return ERR_FILE;

    //Первый ввод
    if (fscanf(file, "%lf", &number) != 1)
        return ERR_IO;
    do
    {
        *average += number;
        count++;
    } while (fscanf(file, "%lf", &number) == 1);

    if (count == 0)
        return ERR_IO;
    
    *average = *average / count;

    return EXIT_SUCCESS;
}

double compute_disperse(FILE *file, double average)
{
    double number;
    int count = 0;
    double dispersion = 0.0;
    if (fseek(file, 0, SEEK_SET) != 0)
        return ERR_FILE;
        
    while (fscanf(file, "%lf", &number) == 1)
    {
        // printf("%lf\n", dispersion);
        dispersion += (number - average) * (number - average);
        count++;
    } 
    dispersion = dispersion / count;

    return dispersion;
}
