#include "matrix.h"
#include "matrix_alloc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

errors_t matrix_copy(const matrix_t *src, matrix_t *dst)
{
    free_matrix(dst, dst->rows);
    // double **ptrs, *data;
    //
    // ptrs = malloc((src->rows + 1) * sizeof(double *));
    // if (!ptrs)
    //     return ERR_MEM;
    // data = malloc(src->rows * src->cols * sizeof(double));
    // if (!data)
    // {
    //     free(ptrs);
    //     return ERR_MEM;
    // }

    if (matrix_alloc(dst, src->rows, src->cols) != EXIT_SUCCESSFUL)
        return ERR_MEM;
    
    for (size_t i = 0; i < src->rows; i++)
    {
        memcpy(dst->matrix[i], src->matrix[i], src->cols * sizeof(double));
    }
    // memcpy(dst->matrix[0], src->matrix[0], src->rows * src->cols * sizeof(double));
    // memcpy(data, src->matrix[0], src->rows * src->cols * sizeof(double));
    // *ptrs = data; 
    // ptrs[src->rows] = data;
    // for (size_t i = 1; i < src->rows; i++)
    //     ptrs[i] = data + i * src->cols;
    // dst->matrix = ptrs;
    // dst->cols = src->cols;
    // dst->rows = src->cols;

    return EXIT_SUCCESSFUL;
}

/**
 * @brief Функция для заполнения матрицы из файла
 *
 * @param[in] file Файловый указатель
 * @param[out] matrix Указатель на матрицу
 * @param[in] count Количество чисел в файле
 * @return 
 */
static errors_t fill_matrix(FILE *file, matrix_t *matrix, size_t count)
{
    errors_t rc = EXIT_SUCCESSFUL;
    size_t i = 0;
    size_t rows = 0, cols = 0;
    double value = 0.0;


    for (; i < count + 1 && !rc; i++)
    {
        if (fscanf(file, "%zu %zu %lf", &rows, &cols, &value) != 3)
            rc = ERR_IO;
        
        if (rows == 0 || cols == 0 || rows > matrix->rows || cols > matrix->cols || i >= count)
            rc = ERR_IO;
        if (!rc)
            matrix->matrix[rows - 1][cols - 1] = value;
    }
    
    if (rc && feof(file) && (i - 1) == count)
        rc = EXIT_SUCCESSFUL;

    return rc;
}

errors_t read_matrix(FILE *file, matrix_t *matrix)
{
    errors_t rc;
    size_t rows, cols, count;

    if (fscanf(file, "%zu %zu %zu", &rows, &cols, &count) != 3)
    {
        return ERR_IO;
    }

    if (rows == 0 || cols == 0)
        return ERR_EMPTY;

    if (count > rows * cols)
        return ERR_IO;
    
    rc = matrix_alloc(matrix, rows, cols);
    if (rc)
        return rc;
    
    matrix_set_zero(matrix);
    return fill_matrix(file, matrix, count);
}

errors_t read_matrix_ex(char *filename, matrix_t *matrix)
{
    errors_t rc;

    FILE *file = fopen(filename, "r");
    if (!file)
        return ERR_IO;

    rc = read_matrix(file, matrix);
    fclose(file);
    
    return rc;
}

void print_matrix(FILE *file, const matrix_t *matrix)
{
    fprintf(file, "%zu %zu\n", matrix->rows, matrix->cols);

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
            fprintf(file, "%lf ", matrix->matrix[i][j]);
        fprintf(file, "\n");
    }
}

errors_t print_matrix_ex(char *filename, const matrix_t *matrix)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return ERR_IO;
    print_matrix(file, matrix);
    fclose(file);

    return EXIT_SUCCESSFUL;
}

void matrix_set_zero(matrix_t *matrix)
{
    if (!matrix)
        return;

    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            matrix->matrix[i][j] = 0.0;
}

