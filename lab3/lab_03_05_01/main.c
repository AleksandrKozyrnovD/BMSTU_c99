#include "arrays.h"
#include "inputoutput.h"

int main(void)
{
    size_t rows, columns, size = 0;
    int matrix[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    int array[MAX_ARRAY_SIZE * MAX_ARRAY_SIZE];
    //bool mask[MAX_ARRAY_SIZE * MAX_ARRAY_SIZE] = { false };

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

    if (collect_array(matrix, rows, columns, array, &size) != EXIT_SUCCESS)
    {
        printf("Нет чисел, сумма цифр которых больше десяти\n");
        return ERR_TASK;
    }

    cycle(array, size, 3);

    insert_in_matrix(matrix, rows, columns, array);

    print_matrix(matrix, rows, columns);

    return EXIT_SUCCESS;
}
