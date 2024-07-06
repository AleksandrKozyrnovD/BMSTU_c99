#include "matrix_operations.h"
#include "matrix.h"
#include "matrix_alloc.h"
#include <math.h>
#include <stdio.h>


/**
 * @brief Создание дополненной матрицы
 *
 * @param[in] matrix Указатель на матрицу
 * @param[out] aug Указатель на дополненную матрицу
 * @return Код ошибки
 */
static errors_t get_augmented_matrix(const matrix_t *matrix, matrix_t *augmented)
{
    errors_t rc = EXIT_SUCCESSFUL;

    augmented->matrix = NULL; //Дополненная матрица
    /*
     * Для матрицы 3 на 3 будет примерно такой:
     *
     * A B C        A B C 1 0 0
     * D E F   ---> D E F 0 1 0
     * G K L        G K L 0 0 1
     * */


    /*
     * Выделяем память на n строк и на 2*n столбцов. Считается, что исходная матрица квадратная
     * */
    rc = matrix_alloc(augmented, matrix->rows, 2 * matrix->rows);
    if (rc)
        return rc;
    
    matrix_set_zero(augmented);

    /*
     * Заполнение двух половинок матрицы
     * */
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            augmented->matrix[i][j] = matrix->matrix[i][j]; //Элементы исходной матрицы
            augmented->matrix[i][j + matrix->rows] = (i == j); //Элементы единичной матрицы. Если i == j (диагональ), то единица, иначе нуль
                                                               //Смещение в строке относительно начала равна кол-ву столбцов (строчек) (но это
                                                               // неважно, так как она квадратная)
        }
    }
    
    return EXIT_SUCCESSFUL;
}

/**
 * @brief Функция для перемещения между собой двух строк матрицы. Считается, что строки существуют
 *
 * @param[in,out] matrix Указатель на матрицу
 * @param[in] row1 Первая строка
 * @param[in] row2 Вторая строка
 */
static void swap_row(matrix_t *matrix, size_t row1, size_t row2)
{
    double *tmp = matrix->matrix[row1];
    matrix->matrix[row1] = matrix->matrix[row2];
    matrix->matrix[row2] = tmp;
}

/**
 * @brief Функция для умножения строки матрицы на число
 *
 * @param[in,out] matrix Указатель на матрицу
 * @param[in] row Умножаемая строка
 * @param[in] factor Число, на которое умножаем
 */
static void scale_row(matrix_t *matrix, size_t row, double factor)
{
    for (size_t j = 0; j < matrix->cols; j++)
    {
        matrix->matrix[row][j] /= factor;
    }
}

/**
 * @brief Линейная комбинация двух строк матрицы
 *
 * @param[in,out] matrix Указатель на матрицу
 * @param[in] row1 К какой строке прибавляется другая строка
 * @param[in] row2 Прибавляемая строка
 * @param[in] factor На сколько следует умножить вторую строку
 */
static void linear_combination(matrix_t *matrix, size_t row1, size_t row2, double factor)
{
    for (size_t j = 0; j < matrix->cols; j++)
        matrix->matrix[row1][j] -= matrix->matrix[row2][j] * factor;
}

/**
 * @brief Функция для получения верхнетреугольной матрицы
 *
 * @param[in,out] matrix Указатель на матрицу
 */
static void make_upper_triangle(matrix_t *matrix)
{
    /*
     * Считается, что матрица на входе квадратная, либо дополненная к квадратной
     * */
    size_t n = matrix->rows;
    matrix_t augmented = *matrix;
    double factor;
    //double leading = augmented.matrix[i][i];
    for (size_t i = 0; i < n; i++)
    {
        size_t pivot_row = i; //Выбираем первую строчку, в которой текущее (i-е по столбцу) значение ненулевое
        for (size_t j = i + 1; j < n; j++)
        {
            //Если в новой строчке на этом месте не нуль, а на текущей нуль, то меняем их местами.
            // if (fabs(augmented.matrix[j][i]) > MACHINE_ZERO && fabs(augmented.matrix[pivot_row][i]) < MACHINE_ZERO)
            if (fabs(augmented.matrix[j][i]) > MACHINE_ZERO && fabs(augmented.matrix[pivot_row][i]) - fabs(augmented.matrix[j][i]) > 0.0)
            {
                pivot_row = j;
                // break;
            }
        }

        //Меняем их местами (переставляем строчки местами)
        if (pivot_row != i)
            swap_row(&augmented, i, pivot_row);

        factor = augmented.matrix[i][i]; //Текущий диагональный элемент

        /*
         * На нуль делить нельзя.
         * Однако если он все же оказался нуль во всем столбце, то обратной матрицы не существует.
         * По-хорошему уже тут следовало бы возвращать код ошибки и даже, наверное, не считать определитель матрицы
         * Видимо оставил зачем-то зачем уже сам не знаю. 
         * */
        if (fabs(factor) < MACHINE_ZERO)
            continue;
        scale_row(&augmented, i, factor); //Делим текущую строчку (i-ю) на диагональный эл-нт, чтобы получить по диагонали единицу

        for (size_t j = i + 1; j < augmented.rows; j++)
        {
            /*старая проверка, вроде как щас не нужна, но пусть пока что будет здесь*/
            if (j != i)
            {
                /*
                 * Следущие две строчки превращают все цифры под текущим диагональным элементом в 0
                 *
                 * 1 2   ---> 1 2 для первого диагонального элемента (1)
                 * 2 5        0 1
                 * */
                factor = augmented.matrix[j][i]; 
                /*
                 * Текущая_строка - (factor * Другая_строка)
                 *
                 * В нашем случае:
                 * От j-ой строки отнять factor * i-ю строку
                 * */
                linear_combination(&augmented, j, i, factor);
            }
        }
    }
}

/**
 * @brief Создание диагональной матрицы из верхнетреугольной
 *
 * @param[in,out] matrix Указатель на матрицу
 */
static void make_diagonal(matrix_t *matrix)
{
    /*
     * Считается, что матрица к этому моменту уже верхнетреугольная
     *
     * Идем с последней строчки до самой первой.
     *
     * Мы знаем, что к текущему моменту на диагонали находятся только единицы.
     * Поэтому легко ищется фактор, и он равен элементу над текущим эл-ом диагонали.
     *
     * Выбор do {} while обусловлен тем, что нам всегда необходимо сделать n - 1 операцию. Операции заканчиваются на 1-ой строчке.
     * Однако, если в матрице 2 строчки, то простой алгоритм не сможет такое обработать (из-за особенностей size_t)
     * */
    double factor;
    size_t j;
    for (size_t i = matrix->rows - 1; i >= 1; i--)
    {
        j = i;
        do
        {
            j--;
            factor = matrix->matrix[j][i];
            linear_combination(matrix, j, i, factor);
        }
        while (j != 0);
    }
}

/**
 * @brief Метод элементарных преобразований
 *
 * @param[in,out] matrix Указатель на матрицу
 */
static void gauss_jordan_elimination(matrix_t *matrix)
{
    /*
     * Элементарные преобразования делаются в два этапа:
     * 1) Сделать текущую матрицу верхнетреугольной
     * 2) Сделать ее диагональной
     * */
    make_upper_triangle(matrix);
    make_diagonal(matrix);
}

/**
 * @brief Функция превращения матрицы в верхнетреугольную. Отличается от своего сородича тем, что не делит строки на диагональный элемент
 *
 * @param[in] matrix Указатель на матрицу
 */
static void make_upper_triangle_det(matrix_t *matrix)
{
    /*
     * На 99% схожая функция с make_upper_triangle. Знаком !!! будет показано и объяснено, что здесь и почему отличается
     * */
    size_t n = matrix->rows;
    matrix_t augmented = *matrix;
    double factor;
    for (size_t i = 0; i < n - 1; i++)
    {
        size_t pivot_row = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (fabs(augmented.matrix[j][i]) > MACHINE_ZERO && fabs(augmented.matrix[pivot_row][i]) < MACHINE_ZERO)
            {
                pivot_row = j;
                break;
            }
        }

        if (pivot_row != i)
            swap_row(&augmented, i, pivot_row);
        
        /*
         * !!! !!! !!!
         * Мы до сих пор проверяем, состоит ли текущий столбец полностью из нулей.
         * Если состоит из нулей, с ним мы ничего не делаем.
         *
         * Однако разница с оригинальным алгоритмом состоит в том, что мы НЕ делим текущую строчку на ее диагональный элемент.
         * В случае, если бы делили, получали определитель, равный 1.
         *
         * В этом месте можно с уверенностью в 100% сказать, что определитель равен нулю и ничего дальше не считать.
         *
         * Скорее всего, так и следовало бы сделать
         * */
        factor = augmented.matrix[i][i];
        if (fabs(factor) < MACHINE_ZERO)
            continue;
        
        for (size_t j = i + 1; j < augmented.rows; j++)
        {
            if (j != i)
            {
                factor = augmented.matrix[j][i] / augmented.matrix[i][i];
                linear_combination(&augmented, j, i, factor);
            }
        }
    }
}

double gauss_determinant(matrix_t *matrix)
{
    /*
     * Определитель с помощью элементарных преобразований делится на 2 этапа:
     * 1) Сделать матрицу верхнетреугольной (диагональные элементы не трогать)
     * 2) Перемножить диагональные элементы
     *
     * Почему это работает? Это работает потому, что единственный ненулевой
     * минор такой матрицы будет находится для элемента с индексом 1, 1 (для прогр. 0, 0).
     * Это можно показать на следующей матрице:
     * 1 2 3
     * 0 5 6
     * 0 0 9
     *
     * Разложим матрицу на миноры по первой строчке и сложим их значения, чтобы найти определитель
     * Минор для 1: 1 * (5 * 9 - 0 * 6) = 45
     * Минор для 2: 2 * (0 * 9 - 0 * 6) = 0
     * Минор для 3: 3 * (0 * 0 - 0 * 5) = 0
     *
     * Определитель = 45 + 0 + 0
     * */
    make_upper_triangle_det(matrix);
    double det = 1.0;
    for (size_t i = 0; i < matrix->rows; i++)
        det *= matrix->matrix[i][i];

    return det;
}

errors_t get_inverse_matrix(const matrix_t *source, matrix_t *result)
{
    /*
     * Объединение всех ранее описанных функций в одну. Память под result не выделяется, зато проверяется корректность ее заполненности
     * */
    errors_t rc;
    if (source->rows != source->cols)
        return ERR_IO;

    if (result->rows != source->rows || result->cols != source->rows)
        return ERR_IO;

    size_t n = source->rows; //Размер матрицы
    
    matrix_t augmented = { .matrix = NULL, .cols = 0, .rows = 0 }; //Дополненная матрица создается тут
    rc = get_augmented_matrix(source, &augmented);                 // <-------------------------------|
    if (rc)
        return rc;

    gauss_jordan_elimination(&augmented); //Применяем метод элементарных преобразований к дополненной матрице
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            result->matrix[i][j] = augmented.matrix[i][j + n]; //Списываем элементы в результирующую
                                                               //Стоит заметить, что нужные элементы в дополненной матрице
                                                               //лежат со смещением в строке от ее начала на кол-во столбцов (n).
        }
    }

    free_matrix(&augmented, augmented.rows);

    return EXIT_SUCCESSFUL;
}

errors_t add(const matrix_t *left, const matrix_t *right, matrix_t *res)
{
    if (left->rows != right->rows || left->cols != right->cols || left->rows != res->rows || left->cols != res->cols)
        return ERR_RANGE;

    for (size_t i = 0; i < left->rows; i++)
    {
        for (size_t j = 0; j < left->cols; j++)
            res->matrix[i][j] = left->matrix[i][j] + right->matrix[i][j];
    }

    return EXIT_SUCCESSFUL;
}

errors_t multiply(const matrix_t *left, const matrix_t *right, matrix_t *res)
{
    matrix_set_zero(res);
    // double k = 0.0;
    if (left->cols != right->rows)
        return ERR_RANGE;
    if (res->rows != left->rows || res->cols != right->cols)
        return ERR_RANGE;
    
    for (size_t i = 0; i < left->rows; i++)
    {
        for (size_t j = 0; j < right->cols; j++)
        {
            // k = 0.0;
            for (size_t m = 0; m < left->cols; m++)
                res->matrix[i][j] += left->matrix[i][m] * right->matrix[m][j];
            // res->matrix[i][j] = k;
        }
    }

    return EXIT_SUCCESSFUL;
}

