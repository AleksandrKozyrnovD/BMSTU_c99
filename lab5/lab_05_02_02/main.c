#include <stdio.h>
#include "process.h"
#include "errorcode.h"

#define MAX_ARRAY_SIZE 10


int main(int argc, char **argv)
{
    double average;

    if (argc != 2)
        return ERR_COMMAND;

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Введенного файла не существует\n");
        return ERR_FILE;
    }
    
    if (get_average(file, &average) != EXIT_SUCCESS)
    {
        printf("Файл неверно заполнен\n");
        return ERR_IO;
    }
    // printf("%lf\n", average);

    // fseek(file, 0, SEEK_SET);
    printf("%lf\n", compute_disperse(file, average));

    fclose(file);

    return EXIT_SUCCESS;
}
