#include "additionals.h"



int b2t(FILE *file_source, FILE *file_dst)
{
    if (fseek(file_source, 0, SEEK_END) != 0)
        return ERR_IO;
    
    long size = ftell(file_source);
    if (size == -1)
        return ERR_FILE;
    
    if (size % sizeof(int) != 0)
        return ERR_IO;
    
    if (fseek(file_source, 0, SEEK_SET) != 0)
        return ERR_IO;
    
    int number;

    size = size / sizeof(int);
    for (long i = 0; i < size; i++)
    {
        if (fread(&number, sizeof(int), 1, file_source) != 1)
            return ERR_IO;
        fprintf(file_dst, "%d\n", number);
    }

    return EXIT_SUCCESS;
}

int t2b(FILE *file_source, FILE *file_dst)
{
    if (fseek(file_source, 0, SEEK_END) != 0)
        return ERR_IO;
    
    if (fseek(file_source, 0, SEEK_SET) != 0)
        return ERR_IO;

    int number;
    while (fscanf(file_source, "%d", &number) == 1)
    {
        if (fwrite(&number, sizeof(int), 1, file_dst) != 1)
            return ERR_IO;
    }

    return EXIT_SUCCESS;
}
