#include "arrays.h"


bool have_digit(int number, int digit)
{
    number = abs(number);
    do
    {
        if (number % 10 == digit)
            return true;
        number /= 10;
    } while (number);

    return false;
}


bool is_column_has_digit(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t column_index, int digit)
{
    for (size_t i = 0; i < rows; i++)
    {
        if (have_digit(matrix[i][column_index], digit))
            return true;
    }
    return false;
}


void delete(int *array, size_t size, size_t index)
{
    for (size_t j = index; j < size; j++)
    {
        array[j] = array[j + 1];
    }
}

void delete_column(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t *columns, size_t index)
{
    (*columns)--;
    for (size_t i = 0; i < rows; i++)
    {
        delete(matrix[i], *columns, index);
        /*
        for (size_t j = index; j < *columns; j++)
        {
            matrix[i][j] = matrix[i][j + 1];
        }
        */
    }
}

int find_all_columns(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns, size_t *columns_delete, size_t *amount, size_t digit)
{
    *amount = 0;
    for (size_t j = 0; j < columns; j++)
    {
        if (is_column_has_digit(matrix, rows, j, digit))
        {
            columns_delete[*amount] = j;
            (*amount)++;
        }
    }

    if (*amount == columns)
        return ERR_TASK;
    return EXIT_SUCCESS;
}

int delete_all_columns(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t *columns, size_t digit)
{
    size_t what_columns_to_delete[MAX_ARRAY_SIZE];
    size_t size_delete = 0;

    if (find_all_columns(matrix, rows, *columns, what_columns_to_delete, &size_delete, digit) != EXIT_SUCCESS)
        return ERR_TASK;

    if (size_delete == 0)
        return EXIT_SUCCESS;

    for (size_t i = size_delete - 1; i > 0; i--)
    {
        delete_column(matrix, rows, columns, what_columns_to_delete[i]);
    }

    delete_column(matrix, rows, columns, what_columns_to_delete[0]);

    return EXIT_SUCCESS;
}
