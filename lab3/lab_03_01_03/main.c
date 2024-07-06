#include "arrays.h"
#include "inputoutput.h"

#define MAX_ARRAY_SIZE 10


int main(void)
{
    size_t rows, columns;
    int matrix[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    int array[MAX_ARRAY_SIZE];
    
    int rc = validate_input_size(&rows, &columns);
    switch (rc)
    {
        case ERR_IO:
            printf("Неверный ввод количества строк или столбцов");
            return rc;
        case ERR_RANGE:
            printf("Столбцы и строчки должны лежать от единицы до десяти включительно");
            return rc;
        case EXIT_SUCCESS:
            break;
        default:
            return ERR_TASK;
    }
    
    if (input_matrix(matrix, rows, columns) != EXIT_SUCCESS)
    {
        printf("Ошибка в заполнении матрицы\n");
        return ERR_IO;
    }
    
    find_sequence(matrix, rows, columns, array);

    print_array(array, rows);

    return EXIT_SUCCESS;
}
