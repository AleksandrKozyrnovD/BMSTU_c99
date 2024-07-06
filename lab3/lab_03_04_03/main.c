#include "arrays.h"
#include "inputoutput.h"

int main(void)
{
    size_t rows, columns;
    int matrix[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    
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

    if (rows != columns)
    {
        printf("Матрица не квадратная");
        return ERR_IO;
    }

    reshape_matrix(matrix, rows);
    
    print_matrix(matrix, rows, columns);

    return EXIT_SUCCESS;
}
