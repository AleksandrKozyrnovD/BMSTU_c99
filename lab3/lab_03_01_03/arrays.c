#include "arrays.h"


bool is_sequence(const int *array, size_t size)
{
    bool result = true;
    int current_value;
    
    if (size == 1)
        return false;

    //Нахождение неубывающей последовательности
    current_value = array[0];
    size_t i = 1;
    do
    {
        if (current_value > array[i])
            result = false;
        current_value = array[i];
        i++;
    } while (i < size && result == true);

    /*
    for (size_t i = 1; i < size; i++)
    {
        if (current_value > array[i])
        {
            result = false;
            break;
        }
        current_value = array[i]; 
    }
    */
    if (result == true)
        return true;
    
    
    //Нахождение невозврастабщей последовательности
    result = true;
    current_value = array[0];
    i = 1;
    do
    {
        if (current_value < array[i])
            result = false;
        current_value = array[i];
        i++;
    } while (i < size && result == true);
    
    /*
    for (size_t i = 1; i < size; i++)
    {
        if (current_value < array[i])
        {
            return false;
        }
        current_value = array[i];
    }
    */
        
    return result;
}


void find_sequence(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns, int *array)
{
    for (size_t k = 0; k < rows; k++)
    {
        if (is_sequence(matrix[k], columns))
            array[k] = 1;
        else
            array[k] = 0;
    }
}
