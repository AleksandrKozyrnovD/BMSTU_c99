#include "check_matrix_alloc.h"


//Выделение памяти

/*
 * Память выделена
 * */
START_TEST(pos_1)
{
    matrix_t a = { .matrix = NULL };
    errors_t rc = EXIT_SUCCESSFUL;

    rc = matrix_alloc(&a, 2, 2);
    if (a.matrix != NULL)
    {
        ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
        ck_assert_uint_eq(a.rows, 2);
        ck_assert_uint_eq(a.cols, 2);
    }
    else
    {
        ck_assert_int_eq(rc, ERR_MEM);
    }
    free_matrix(&a, a.rows);
}
END_TEST

/*
 * Неверно указан размер матрицы
 * */
START_TEST(neg_1)
{
    matrix_t a = { .matrix = NULL };
    errors_t rc = EXIT_SUCCESSFUL;
    rc = matrix_alloc(&a, 0, 0);
    ck_assert_int_eq(rc, ERR_RANGE);
    ck_assert_ptr_eq(a.matrix, NULL);
    free_matrix(&a, a.rows);
}

Suite *get_matrix_alloc_suite(void)
{
    Suite *suite = suite_create("Matrix teests");

    TCase *tpos = tcase_create("Positive alloc");
    tcase_add_test(tpos, pos_1);

    TCase *tneg = tcase_create("Negative alloc");
    tcase_add_test(tneg, neg_1);

    suite_add_tcase(suite, tpos);
    suite_add_tcase(suite, tneg);

    return suite;
}

