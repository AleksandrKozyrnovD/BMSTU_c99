#include "arrays.h"


int input_matrix(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns)
{
    printf("Input matrix: \n");
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
                return ERR_IO;
        }
        //printf("\n"); //Убрал
    }
    return EXIT_SUCCESS;
}


void print_matrix(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int validate_input_size(size_t *rows, size_t *columns)
{
    printf("Input number of rows: ");
    if (scanf("%zu", rows) != 1)
        return ERR_IO;
    if (0 >= *rows || *rows > MAX_ARRAY_SIZE)
        return ERR_RANGE;

    printf("Input number of columns: ");
    if (scanf("%zu", columns) != 1)
        return ERR_IO;
    if (0 >= *columns || *columns > MAX_ARRAY_SIZE)
        return ERR_RANGE;
    return EXIT_SUCCESS;
}
