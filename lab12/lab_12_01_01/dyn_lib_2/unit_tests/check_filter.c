#include "check_filter.h"
#include <stdlib.h>

/**
 * @brief Функция сравнения двух массивов
 * 
 * @param beg1 Начало первого массива
 * @param end1 Конец первого массива
 * @param beg2 Начало второго массива
 * @param end2 Конец второго массива
 */
static void ck_assert_array_eq(int *beg1, int *end1, int *beg2, int *end2)
{
    ck_assert_int_eq(end1 - beg1, end2 - beg2);

    while (beg1 < end1)
    {
        ck_assert_int_eq(*beg1, *beg2);
        beg1++;
        beg2++;
    }
}

//Позитивные тесты на фильтр
/**
 * @brief Проверка ситуации, когда индекс минимального меньше индекса максимального и между ними есть еще числа
 */
START_TEST(test_pos_1_key)
{
    // index_min < index_max
    int array[] = { 1, 2, 3, 4, 5 };
    int buf[] = { 2, 3, 4 };

    int *filtered_beg = NULL, *filtered_end;

    filtered_beg = malloc(sizeof(int) * 3);
    filtered_end = filtered_beg + 3;
    int rc = key(array, array + 5, filtered_beg);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    ck_assert(filtered_beg != NULL);
    ck_assert_uint_eq(3, filtered_end - filtered_beg);

    ck_assert_array_eq(filtered_beg, filtered_end, buf, buf + 3);
    free(filtered_beg);
}
END_TEST

/**
 * @brief Проверка ситуации, когда индекс минимального больше индекса максимального и между ними есть еще числа
 */
START_TEST(test_pos_2_key)
{
    // index_min > index_max
    int array[] = { 5, 4, 3, 2, 1 };
    int buf[] = { 4, 3, 2 };
    int *filtered_beg = NULL, *filtered_end;

    filtered_beg = malloc(sizeof(int) * 3);
    filtered_end = filtered_beg + 3;

    int rc = key(array, array + 5, filtered_beg);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    ck_assert(filtered_beg != NULL);
    ck_assert_uint_eq(3, filtered_end - filtered_beg);

    ck_assert_array_eq(filtered_beg, filtered_end, buf, buf + 3);
    free(filtered_beg);
}
END_TEST


/**
 * @brief Проверка ситуации, когда после фильтрации останется ровно 1 число и индекс минимального меньше максимального
 */
START_TEST(test_pos_3_key)
{
    // index_min < index_max && index_max - index_min == 1
    int array[] = { 1, 2, 3 };
    int buf[] = { 2 };

    int *filtered_beg = NULL, *filtered_end;

    filtered_beg = malloc(sizeof(int) * 1);
    filtered_end = filtered_beg + 1;

    int rc = key(array, array + 3, filtered_beg);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    ck_assert(filtered_beg != NULL);
    ck_assert_uint_eq(1, filtered_end - filtered_beg);
    ck_assert_array_eq(filtered_beg, filtered_end, buf, buf + 1);
    free(filtered_beg);
}
END_TEST


/**
 * @brief Проверка ситуации, когда после фильтрации останется ровно 1 число и индекс максимального меньше минимального
 */
START_TEST(test_pos_4_key)
{
    // index_min > index_max && index_mid - index_max == 1
    int array[] = { 3, 2, 1 };
    int buf[] = { 2 };
    int *filtered_beg = NULL, *filtered_end;

    filtered_beg = malloc(sizeof(int) * 1);
    filtered_end = filtered_beg + 1;

    int rc = key(array, array + 3, filtered_beg);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    ck_assert(filtered_beg != NULL);
    ck_assert_uint_eq(1, filtered_end - filtered_beg);
    ck_assert_array_eq(filtered_beg, filtered_end, buf, buf + 1);

    free(filtered_beg);
}
END_TEST


//Негативные тесты
/**
 * @brief Проверка ошибочной ситуации, когда подается неправильный указатель на массив
 */
START_TEST(test_neg_1_key)
{
    //pointers are null or uninitialized
    int *filtered_beg = NULL;//, *filtered_end;
    int *array = NULL;

    int rc = key(array, array, filtered_beg);
    ck_assert_int_eq(rc, ERR_IO);
    ck_assert(filtered_beg == NULL);

    int arr[] = { 1, 2, 3 };
    rc = key(arr, arr + 3, NULL);
    ck_assert_int_eq(rc, ERR_IO);
}
END_TEST

/**
 * @brief Проверка ошибочной ситуации, когда указатель на конец меньше указателя на начало (перепутали начало и конец)
 */
START_TEST(test_neg_2_key)
{
    int *filtered_beg = NULL;//, *filtered_end;
    int array[] = { 1, 2, 3 };

    int rc = key(array + 3, array, filtered_beg);
    ck_assert_int_eq(rc, ERR_IO);
    ck_assert(filtered_beg == NULL);
}
END_TEST

/**
 * @brief Проверка ошибочной ситуации, когда после фильтрации ничего не останется
 */
START_TEST(test_neg_3_key)
{
    //nothing was left after filtering-out
    int *filtered_beg = NULL;//, *filtered_end;
    int array[] = { 1, 3 };

    int rc = key(array, array + 2, filtered_beg);
    ck_assert_int_eq(rc, ERR_IO);
    ck_assert(filtered_beg == NULL);
}
END_TEST

/**
 * @brief Проверка ошибочной ситуации, когда в файле только одно число, но повторяется много раз. Пример: 3 3 3 3
 */
START_TEST(test_neg_4_key)
{
    //min == max
    int *filtered_beg = NULL;//, *filtered_end;
    int array[] = { 3, 3, 3, 3 };

    int rc = key(array, array + 4, filtered_beg);
    ck_assert_int_eq(rc, ERR_IO);
    ck_assert(filtered_beg == NULL);
}
END_TEST

Suite *get_filter_suite(void)
{
    Suite *suite = suite_create("Filter tests");

    TCase *tc_pos = tcase_create("Positives");
    tcase_add_test(tc_pos, test_pos_1_key);
    tcase_add_test(tc_pos, test_pos_2_key);
    tcase_add_test(tc_pos, test_pos_3_key);
    tcase_add_test(tc_pos, test_pos_4_key);
    suite_add_tcase(suite, tc_pos);

    TCase *tc_neg = tcase_create("Negatives");
    tcase_add_test(tc_neg, test_neg_1_key);
    tcase_add_test(tc_neg, test_neg_2_key);
    tcase_add_test(tc_neg, test_neg_3_key);
    tcase_add_test(tc_neg, test_neg_4_key);
    suite_add_tcase(suite, tc_neg);

    return suite;
}
