#include "check_matrix_operations.h"
#include "errors.h"
#include "matrix.h"
#include "matrix_operations.h"
#include <check.h>
#include <stdio.h>

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
    // print_matrix(stdout, a);
    // print_matrix(stdout, b);
    if (a->rows != b->rows || a->cols != b->cols)
        return 1;
    
    // printf("Sizes equal\n");
    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < a->cols; j++)
        {
            if (fabs(a->matrix[i][j] - b->matrix[i][j]) > ZERO)
            {
                // printf("Elem at index %zu %zu not equal\nval1 = %lf, val2 = %lf\n", i, j, a->matrix[i][j], b->matrix[i][j]);
                return 1;
            }
        }
    }

    return 0;
}


//Сложение

/*
 * Сложение удачно прошло
 * */
START_TEST(add_pos_1)
{
    printf("Add pos 1\n");
    matrix_t a = { .matrix = NULL };
    matrix_t b = { .matrix = NULL };
    matrix_t c = { .matrix = NULL };
    matrix_t d = { .matrix = NULL };

    errors_t rc = EXIT_SUCCESSFUL;

    rc = matrix_alloc(&a, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(a.rows, 2);
    ck_assert_uint_eq(a.cols, 2);
    matrix_set_zero(&a);
    a.matrix[0][0] = 1;
    a.matrix[1][1] = 1;

    rc = matrix_alloc(&b, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(b.rows, 2);
    ck_assert_uint_eq(b.cols, 2);
    matrix_set_zero(&b);
    b.matrix[0][1] = 1;
    b.matrix[1][0] = 1;

    rc = matrix_alloc(&c, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(c.rows, 2);
    ck_assert_uint_eq(c.cols, 2);

    rc = matrix_alloc(&d, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(d.rows, 2);
    ck_assert_uint_eq(d.cols, 2);
    d.matrix[0][0] = 1.0;
    d.matrix[0][1] = 1.0;
    d.matrix[1][0] = 1.0;
    d.matrix[1][1] = 1.0;

    rc = add(&a, &b, &c);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_int_eq(matrix_cmp(&c, &d), 0);

    free_matrix(&a, a.rows);
    free_matrix(&b, b.rows);
    free_matrix(&c, c.rows);
    free_matrix(&d, d.rows);
}
END_TEST


/*
 * Сложение неудачно прошло - не совпали размеры матриц
 * */
START_TEST(add_neg_1)
{
    matrix_t a = { .matrix = NULL };
    matrix_t b = { .matrix = NULL };
    matrix_t c = { .matrix = NULL };

    errors_t rc = EXIT_SUCCESSFUL;

    rc = matrix_alloc(&a, 2, 3);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(a.rows, 2);
    ck_assert_uint_eq(a.cols, 3);
    matrix_set_zero(&a);
    a.matrix[0][0] = 1;
    a.matrix[1][1] = 1;

    rc = matrix_alloc(&b, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(b.rows, 2);
    ck_assert_uint_eq(b.cols, 2);
    matrix_set_zero(&b);
    b.matrix[0][1] = 1;
    b.matrix[1][1] = 1;

    rc = matrix_alloc(&c, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(c.rows, 2);
    ck_assert_uint_eq(c.cols, 2);


    rc = add(&a, &b, &c);
    ck_assert_int_eq(rc, ERR_RANGE);

    free_matrix(&a, a.rows);
    free_matrix(&b, b.rows);
    free_matrix(&c, c.rows);
}

//Умножение
/*
 * Умножение прошло удачно
 * */
START_TEST(mul_pos_1)
{
    matrix_t a = { .matrix = NULL };
    matrix_t b = { .matrix = NULL };
    matrix_t c = { .matrix = NULL };
    matrix_t d = { .matrix = NULL };

    errors_t rc = EXIT_SUCCESSFUL;

    rc = matrix_alloc(&a, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(a.rows, 2);
    ck_assert_uint_eq(a.cols, 2);
    matrix_set_zero(&a);
    a.matrix[0][0] = 2;
    a.matrix[1][1] = 2;

    rc = matrix_alloc(&b, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(b.rows, 2);
    ck_assert_uint_eq(b.cols, 2);
    matrix_set_zero(&b);
    b.matrix[0][0] = 2;
    b.matrix[1][1] = 2;

    rc = matrix_alloc(&c, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(c.rows, 2);
    ck_assert_uint_eq(c.cols, 2);

    rc = matrix_alloc(&d, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(d.rows, 2);
    ck_assert_uint_eq(d.cols, 2);
    matrix_set_zero(&d);
    d.matrix[0][0] = 4;
    d.matrix[1][1] = 4;

    rc = multiply(&a, &b, &c);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_int_eq(matrix_cmp(&c, &d), 0);

    free_matrix(&a, a.rows);
    free_matrix(&b, b.rows);
    free_matrix(&c, c.rows);
    free_matrix(&d, d.rows);
}
END_TEST

/*
 * Умножение прошло неудачно
 * */
START_TEST(mul_neg_1)
{
    matrix_t a = { .matrix = NULL };
    matrix_t b = { .matrix = NULL };
    matrix_t c = { .matrix = NULL };

    errors_t rc = EXIT_SUCCESSFUL;

    rc = matrix_alloc(&a, 2, 3);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(a.rows, 2);
    ck_assert_uint_eq(a.cols, 3);
    matrix_set_zero(&a);
    a.matrix[0][0] = 2;
    a.matrix[1][1] = 2;

    rc = matrix_alloc(&b, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(b.rows, 2);
    ck_assert_uint_eq(b.cols, 2);
    matrix_set_zero(&b);
    b.matrix[0][0] = 2;
    b.matrix[1][1] = 2;

    rc = matrix_alloc(&c, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(c.rows, 2);
    ck_assert_uint_eq(c.cols, 2);


    rc = multiply(&a, &b, &c);
    ck_assert_int_eq(rc, ERR_RANGE);

    free_matrix(&a, a.rows);
    free_matrix(&b, b.rows);
    free_matrix(&c, c.rows);
}
END_TEST

//Определитель матрицы
/*
 * Ненулевой определитель
 * */
START_TEST(det_pos_1)
{
    errors_t rc = EXIT_SUCCESSFUL;
    matrix_t a = { .matrix = NULL };

    rc = read_matrix_ex("func_tests/data/mtr/2x2.txt", &a);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    
    ck_assert_uint_eq(a.rows, a.cols);
    // ck_assert_double_eq(gauss_determinant(&a), -2.0);
    double det = gauss_determinant(&a);
    // printf("Det = %lf\n", det);
    // ck_assert(fabs(gauss_determinant(&a) + 2.0) < ZERO);

    ck_assert(fabs(det + 2.0) < ZERO);

    free_matrix(&a, a.rows);
}
END_TEST

/*
 * Нулевой определитель
 * */
START_TEST(det_pos_2)
{
    errors_t rc = EXIT_SUCCESSFUL;
    matrix_t a = { .matrix = NULL };

    rc = read_matrix_ex("func_tests/data/mtr/zero_det.txt", &a);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    
    ck_assert_uint_eq(a.rows, a.cols);
    // ck_assert_double_eq(gauss_determinant(&a), -2.0);
    ck_assert(fabs(gauss_determinant(&a) - 0.0) < ZERO);

    free_matrix(&a, a.rows);
}
END_TEST

//Обратная матрица
/*
 * Все посчиталось
 * */
START_TEST(inv_pos_1)
{
    errors_t rc = EXIT_SUCCESSFUL;
    matrix_t a = { .matrix = NULL };
    matrix_t b = { .matrix = NULL };
    matrix_t c = { .matrix = NULL };

    rc = read_matrix_ex("func_tests/data/mtr/2x2.txt", &a);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    
    ck_assert_uint_eq(a.rows, a.cols);

    rc = matrix_alloc(&b, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    b.matrix[0][0] = -2.0;
    b.matrix[0][1] = 1.0;
    b.matrix[1][0] = 1.5;
    b.matrix[1][1] = -0.5;

    rc = matrix_alloc(&c, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    rc = get_inverse_matrix(&a, &c);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    ck_assert_int_eq(matrix_cmp(&c, &b), 0);

    free_matrix(&a, a.rows);
    free_matrix(&b, b.rows);
    free_matrix(&c, c.rows);
}
END_TEST


//Обратная матрица
/*
 * Все посчиталось и при умножении на исходную получилась единичная матрица
 * */
START_TEST(inv_pos_2)
{
    errors_t rc = EXIT_SUCCESSFUL;
    matrix_t a = { .matrix = NULL };
    matrix_t a_inv = { .matrix = NULL };
    matrix_t b = { .matrix = NULL };
    matrix_t c = { .matrix = NULL };

    rc = read_matrix_ex("func_tests/data/mtr/2x2.txt", &a);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    
    ck_assert_uint_eq(a.rows, a.cols);

    rc = matrix_alloc(&b, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    b.matrix[0][0] = 1.0;
    b.matrix[0][1] = 0.0;
    b.matrix[1][0] = 0.0;
    b.matrix[1][1] = 1.0;

    rc = matrix_alloc(&a_inv, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    matrix_set_zero(&a_inv);

    rc = matrix_alloc(&c, 2, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    matrix_set_zero(&c);

    rc = get_inverse_matrix(&a, &a_inv);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    
    rc = multiply(&a, &a_inv, &c);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    ck_assert_int_eq(matrix_cmp(&c, &b), 0);

    free_matrix(&a, a.rows);
    free_matrix(&b, b.rows);
    free_matrix(&c, c.rows);
    free_matrix(&a_inv, a_inv.rows);
}
END_TEST
Suite *get_matrix_operations_suite(void)
{
    Suite *suite = suite_create("Matrix operations teests");

    TCase *tpos = tcase_create("Positive opers");
    tcase_add_test(tpos, add_pos_1);
    tcase_add_test(tpos, mul_pos_1);
    tcase_add_test(tpos, det_pos_1);
    tcase_add_test(tpos, det_pos_2);
    tcase_add_test(tpos, inv_pos_1);
    tcase_add_test(tpos, inv_pos_2);

    TCase *tneg = tcase_create("Negative opers");
    tcase_add_test(tneg, add_neg_1);
    tcase_add_test(tneg, mul_neg_1);

    suite_add_tcase(suite, tpos);
    suite_add_tcase(suite, tneg);

    return suite;
}

