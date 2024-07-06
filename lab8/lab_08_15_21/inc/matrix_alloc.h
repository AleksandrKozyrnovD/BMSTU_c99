#ifndef MATRIX_ALLOC_H__
#define MATRIX_ALLOC_H__

#include <stdio.h>
#include "matrix.h"
#include "errors.h"

/**
 * @brief Функция выделения памяти для матрицы. Инициализирует матрицу с помощью нулей
 *
 * @param[out] matrix Указатель на матрицу
 * @param[in] rows Количество строк
 * @param[in] cols Количество столбцов
 * @return Код ошибки
 */
errors_t matrix_alloc(matrix_t *matrix, size_t rows, size_t cols);

/**
 * @brief Функция освобождения памяти из под матрицы
 *
 * @param[in,out] matrix Указатель на матрицу
 */
void free_matrix(matrix_t *matrix, size_t n);

#endif

