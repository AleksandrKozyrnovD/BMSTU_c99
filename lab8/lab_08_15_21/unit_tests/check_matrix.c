#include "check_matrix.h"
#include "matrix.h"

#define ZERO 0.00001

/**
 * @brief Функция для сравнения двух матриц
 *
 * @param a Первая матрица
 * @param b Вторая матрица
 * @return 0, если равны. 1, если не равны
 */
static int matrix_cmp(const matrix_t *a, const matrix_t *b)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return 1;

    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < a->cols; j++)
        {
            // if (a->matrix[i][j] != b->matrix[i][j])
            if (fabs(a->matrix[i][j] - b->matrix[i][j]) > ZERO)
                return 1;
        }
    }

    return 0;
}

//Копирование матрицы

/*
 * Скопировано удачно
 * */
START_TEST(pos_1)
{
    matrix_t a = { .matrix = NULL };
    matrix_t b = { .matrix = NULL };
    errors_t rc = EXIT_SUCCESSFUL;

    rc = matrix_alloc(&a, 2, 2);
    matrix_set_zero(&a);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    a.matrix[0][0] = 1;
    a.matrix[1][1] = 1;

    rc = matrix_copy(&a, &b);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_int_eq(matrix_cmp(&a, &b), 0);

    free_matrix(&a, a.rows);
    free_matrix(&b, b.rows);
}
END_TEST

Suite *get_matrix_suite(void)
{
    Suite *suite = suite_create("Matrix teests");

    TCase *tc = tcase_create("Copy");
    tcase_add_test(tc, pos_1);
    suite_add_tcase(suite, tc);

    return suite;
}

