#ifndef MATRIX_H__
#define MATRIX_H__

#include <stddef.h>
#include <stdio.h>
#include "errors.h"

typedef struct matrix_t
{
    double **matrix;
    size_t rows, cols;
} matrix_t;

/**
 * @brief Функция печати матрицы в файл
 *
 * @param[in] file Файловый указатель
 * @param[in] matrix Указатель на матрицу
 */
void print_matrix(FILE *file, const matrix_t *matrix);

/**
 * @brief Функция печати матрицы в файл
 *
 * @param[in] filename Имя файла
 * @param[in] matrix Указатель на матрицу
 * @return Код ошибки. Возвратится ненулевой код ошибки, если файл не был открыт
 */
errors_t print_matrix_ex(char *filename, const matrix_t *matrix);

/**
 * @brief Функция считывания матрицы с файла
 *
 * @param[in] file Файловый указатель
 * @param[out] matrix Указатель на матрицу
 * @return Код ошибки
 */
errors_t read_matrix(FILE *file, matrix_t *matrix);

/**
 * @brief Функция считывания матрицы с файла
 *
 * @param filename Имя файла
 * @param matrix Указатель на матрицу
 * @return Код ошибки. Возвратится ненулевой код ошибки, если файл не был открыт
 */
errors_t read_matrix_ex(char *filename, matrix_t *matrix);

/**
 * @brief Функция для копирования матриц (глубокая копия)
 *
 * @param[in] src Указатель на исходную матрицу
 * @param[out] dst Указатель на новую матрицу (память под нее выделять не обязательно)
 * @return Код ошибки
 */
errors_t matrix_copy(const matrix_t *src, matrix_t *dst);

/**
 * @brief Функция записывает нули во все элементы матрицы
 *
 * @param[in,out] matrix Матрица
 */
void matrix_set_zero(matrix_t *matrix);

#endif

