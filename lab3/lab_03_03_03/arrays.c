#include "arrays.h"


void swap_strings(int *string_one, int *string_second, size_t columns)
{
    for (size_t j = 0; j < columns; j++)
    {
        /*
        int temp = matrix[a][j];
        matrix[a][j] = matrix[b][j];
        matrix[b][j] = temp;
        */
        int temp = string_one[j];
        string_one[j] = string_second[j];
        string_second[j] = temp;
    }
}


int get_min(const int *array, size_t size)
{
    int min = array[0];
    for (size_t i = 0; i < size; i++)
    {
        if (min > array[i])
            min = array[i];
    }
    return min;
}


void sort(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows - 1; i++)
    {
        size_t min_string = i;
        for (size_t j = i + 1; j < rows; j++)
        {
            if (get_min(matrix[j], columns) > get_min(matrix[min_string], columns))
                min_string = j;
        }

        if (min_string != i)
            swap_strings(matrix[i], matrix[min_string], columns);
    }
}
