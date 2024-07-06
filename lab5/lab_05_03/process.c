#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int get_file_size(FILE *file, size_t *size)
{
    *size = 0L;

    if (fseek(file, 0L, SEEK_END) != 0)
        return ERR_IO;
    
    long get_size = ftell(file);

    if (get_size < 0 || get_size % sizeof(int) != 0)
        return ERR_IO;
    *size = get_size;

    if (fseek(file, 0L, SEEK_SET) != 0)
        return ERR_IO;
    return EXIT_SUCCESS;
}

int get_number_by_pos(FILE *file, size_t pos)
{
    int number;
    long index = pos * sizeof(int);

    fseek(file, index, SEEK_SET);
    fread(&number, sizeof(int), 1, file);

    return number;
}

int put_number_by_pos(FILE *file, size_t pos, int number)
{
    long index = pos * sizeof(int);

    fseek(file, index, SEEK_SET);
    fwrite(&number, sizeof(int), 1, file);

    return number;
}

// int get_number_by_pos_relative(FILE *file, size_t offset)
// {
//     int number;
//     // long index = ftell(file) + offset * sizeof(int);

//     fseek(file, offset, SEEK_CUR);
//     fread(&number, sizeof(int), 1, file);

//     return number;
// }

int create_file(FILE *file, size_t count)
{
    // FILE *file = fopen(filename, "wb");
    // if (file == NULL)
    //     return ERR_FILE;

    int number;
    size_t wrote;

    srand(0);
    for (size_t i = 0; i < count; i++)
    {
        number = rand() % 1000;

        wrote = fwrite(&number, sizeof(int), 1, file);
        if (wrote != 1)
            return ERR_IO;
    }

    // fclose(file);

    return EXIT_SUCCESS;
}

int print_file(FILE *file, FILE *dst)
{
    // FILE *file = fopen(filename, "rb");
    // if (file == NULL)
    // {
    //     printf("Такого файла не существует\n");
    //     return ERR_FILE;
    // }

    int number;
    size_t read;
    size_t size;
    if (get_file_size(file, &size) != EXIT_SUCCESS)
    {
        // printf("Файл с нулевым размером\n");
        return ERR_IO;
    }
    
    size = size / sizeof(int);

    for (size_t i = 0; i < size; i++)
    {
        read = fread(&number, sizeof(int), 1, file);
        if (read != 1)
        {
            // printf("Информация, которую мы прочитали, некорректная\n");
            return ERR_IO;
        }
        fprintf(dst, "%d\n", number);
    }

    // fclose(file);

    return EXIT_SUCCESS;
}

//Сортировка выбором
void sort(FILE *file, size_t size)
{
    size_t min_index;
    for (size_t i = 0; i < size; i++)
    {
        min_index = i;
        for (size_t j = i + 1; j < size; j++)
        {
            if (get_number_by_pos(file, j) < get_number_by_pos(file, min_index))
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            int temp = get_number_by_pos(file, i);
            put_number_by_pos(file, i, get_number_by_pos(file, min_index));
            put_number_by_pos(file, min_index, temp);
        }
    }
}

int sort_file(FILE *file)
{
    // FILE *file = fopen(filename, "rb+");
    // if (file == NULL)
    // {
    //     printf("Такого файла не существует\n");
    //     return ERR_FILE;
    // }

    size_t size;
    if (get_file_size(file, &size) != EXIT_SUCCESS)
    {
        // printf("Файл с нулевым размером\n");
        return ERR_IO;
    }
    
    size = size / sizeof(int);
    sort(file, size);

    // fclose(file);

    return EXIT_SUCCESS;
}
