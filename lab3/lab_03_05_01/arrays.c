#include "arrays.h"


bool is_digitsum(int number)
{
    int result = 0;
    number = abs(number);
    do
    {
        result += number % 10;
        if (result > 10)
            return true;
        number /= 10;
    } while (number);

    return false;
}



//int collect_array(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns, int *array, size_t *size, bool *mask)

int collect_array(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns, int *array, size_t *size)
{
    size_t index = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (is_digitsum(matrix[i][j]))
            {
                array[*size] = matrix[i][j];
                (*size)++;
            }
            index++;
        }
    }

    if (*size == 0)
    {
        return ERR_TASK;
    }

    return EXIT_SUCCESS;
}



void cycle_shift_left(int *array, size_t size)
{
    int temp = array[0];
    for (size_t i = 0; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }
    array[size - 1] = temp;
}


void cycle(int *array, size_t size, size_t n)
{
    for (size_t i = 0; i < n; i++)
        cycle_shift_left(array, size);
}



//void insert_in_matrix(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns, int *array, bool *mask)

void insert_in_matrix(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns, const int *array)
{
    /*                   | | |
    УБРАНО ИЗ РЕАЛИЗАЦИИ v v v
      Здесь мы ищем начальный индекс в массиве array (Находим наше первое добавленное число в массиве)
      В целом можно привязать это к количеству сдвигов n, но тогда понадобится передавать в функцию это количество
      Общие формулы:
      size > n -------> index = size - n
      size == n - 1 --> index = 1
      size == n ------> index = 0
    */
   /*
    size_t current_index;
    if (size > 3) 
        current_index = size - 3;
    else if (size == 2)
        current_index = 1;
    else
        current_index = 0;
    */

    //Обработка матрицы с помощью маски.
    size_t current_index = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (is_digitsum(matrix[i][j]))
            {
                matrix[i][j] = array[current_index];
                current_index++;
            }
            /*
            //Так как маска - одномерный массив, мы конвертируем строчки и стобцы матрицы в индекс одномерного массива.
            if (mask[i * columns + j])
            {
                matrix[i][j] = array[current_index];
                current_index++;
            }
            */
        }
    }
}
