#include "matrix_alloc.h"
#include <stdlib.h>

errors_t matrix_alloc(matrix_t *matrix, size_t rows, size_t cols)
{
    double **ptrs;

    if (rows == 0 || cols == 0)
        return ERR_RANGE;

    ptrs = calloc(rows, sizeof(double *));
    if (!ptrs)
        return ERR_MEM;
    
    matrix->matrix = ptrs;
    for (size_t i = 0; i < rows; i++)
    {
        matrix->matrix[i] = malloc(cols * sizeof(double));
        if (!ptrs[i])
        {
            free_matrix(matrix, rows);
            return ERR_MEM;
        }
    }
    
    matrix->rows = rows;
    matrix->cols = cols;

    return EXIT_SUCCESSFUL;
}

// errors_t matrix_alloc(matrix_t *matrix, size_t rows, size_t cols)
// {
//     double **ptrs, *data;
//     
//     if (rows == 0 || cols == 0)
//         return ERR_RANGE;
//
//     ptrs = malloc((rows + 1) * sizeof(double *));
//     if (!ptrs)
//         return ERR_MEM;
//     data = calloc(rows * cols, sizeof(double));
//     if (!data)
//     {
//         free(ptrs);
//         return ERR_MEM;
//     }
//     
//     ptrs[rows] = data; //Указатель на начало нашей матрицы
//     *ptrs = data; //lsp ругается. На самом деле можно было и в цикле.
//     for (size_t i = 1; i < rows; i++)
//         ptrs[i] = data + i * cols;
//
//     matrix->matrix = ptrs;
//     matrix->rows = rows;
//     matrix->cols = cols;
//
//     return EXIT_SUCCESSFUL;
// }

void free_matrix(matrix_t *matrix, size_t n)
{
    if (!matrix->matrix)
        return;
    // double *min = matrix->matrix[0];
    //
    // for (size_t i = 1; i < matrix->rows; i++)
    // {
    //     if (min > matrix->matrix[i])
    //         min = matrix->matrix[i];
    // }
    //
    // free(min);
    // free(matrix->matrix[matrix->rows]);
    // free(matrix->matrix);

    for (size_t i = 0; i < n; i++)
    {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    matrix->matrix = NULL;
    matrix->rows = 0;
    matrix->cols = 0;
}

