#include <stdio.h>
#include "process.h"

int process(FILE *file, size_t *count)
{
    int first, second, third;
    //Первый ввод
    if (fscanf(file, "%d%d%d", &first, &second, &third) != 3)
        return ERR_IO;
    
    do
    {
        // printf("%d::%d::%d\n", first, second, third);
        if (second > first && second > third)
            (*count)++;
        first = second;
        second = third;
    } while (fscanf(file, "%d", &third) == 1);

    return EXIT_SUCCESS;
}