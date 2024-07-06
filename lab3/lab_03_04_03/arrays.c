#include "arrays.h"



void reshape_matrix(int matrix[][MAX_ARRAY_SIZE], size_t size)
{
    for (size_t j = 0; j < size / 2 + size % 2; j++)
    {
        for (size_t i = j; i < size - j; i++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][size - j - 1];
            matrix[i][size - j - 1] = temp;
        }
    }
}
