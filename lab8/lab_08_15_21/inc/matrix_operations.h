#ifndef MATRIX_OPERATIONS_H__
#define MATRIX_OPERATIONS_H__

#include "matrix.h"
#include "errors.h"

#define MACHINE_ZERO 0.00001f //1e-5

/**
 * @brief Функция сложения двух матриц в результирующую
 *
 * @param[in] left Первая матрица
 * @param[in] right Вторая матрица
 * @param[in,out] res Результирующая матрица. Под нее память уже должна быть выделена
 * @return Код ошибки
 */
errors_t add(const matrix_t *left, const matrix_t *right, matrix_t *res);

/**
 * @brief Функция умножения двух матриц в результирующую
 *
 * @param[in] left Первая матрица
 * @param[in] right Вторая матрица
 * @param[in,out] res Результирующая матрица. Под нее память уже должна быть выделена
 * @return Код ошибки
 */
errors_t multiply(const matrix_t *left, const matrix_t *right, matrix_t *res);


/**
 * @brief Функция для поиска определителя методом Гаусса
 *
 * @param[in] matrix Указатель на матрицу
 * @return Определитель матрицы
 */
double gauss_determinant(matrix_t *matrix);

/**
 * @brief Функция для нахождения обратной матрицы
 *
 * @param[in] source Исходная матрица
 * @param[in] result Результирующая (обратная). Память под нее уже должна быть выделена
 * @return Код ошибки
 */
errors_t get_inverse_matrix(const matrix_t *source, matrix_t *result);

#endif

