#include "arrays.h"
#include "inputoutput.h"

int main(void)
{
    size_t rows, columns;
    int matrix[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    int digit;
    
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

    printf("Input a digit: ");
    if (scanf("%d", &digit) != 1)
    {
        printf("Ошибка при вводе цифры\n");
        return ERR_IO;
    }
    if (digit < 0 || digit > 9)
    {
        printf("Ошибка при вводе цифры.\n");
        return ERR_IO;
    }
   
    if (delete_all_columns(matrix, rows, &columns, digit))
    {
        printf("Матрица пустая\n");
        return ERR_TASK;
    }
    
    
    print_matrix(matrix, rows, columns);

    return EXIT_SUCCESS;
}
