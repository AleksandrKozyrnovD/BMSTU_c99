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
    
    if (rows != columns)
        return ERR_TASK;

    fill_spiral_matrix(matrix, rows, columns);

    print_matrix(matrix, rows, columns);

    return EXIT_SUCCESS;
}
