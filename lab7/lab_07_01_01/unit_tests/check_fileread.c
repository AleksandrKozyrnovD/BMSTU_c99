#include "check_fileread.h"
#include <check.h>
#include <stdio.h>


/**
 * @brief Сравнитель массивов
 *
 * @param[in] pbeg1 Указатель на начало первого
 * @param[in] pend1 Указатель на конец первого
 * @param[in] pbeg2 Указатель на начало второго
 * @param[in] pend2 Указатель на конец второго
 * @return Разница
 */
static int array_cmp(const int *pbeg1, const int *pend1, const int *pbeg2, const int *pend2)
{
    //Проверка на равенство длин
    int cmp_score = (pend1 - pbeg1) - (pend2 - pbeg2);
    if (cmp_score)
        return cmp_score;
    
    //Проверка на равенство элементов
    const int *pcur1 = pbeg1, *pcur2 = pbeg2;
    for (; pcur1 < pend1; pcur1++, pcur2++)
    {
        if (*pcur1 != *pcur2)
            return *pcur1 - *pcur2;
    }

    return 0;
}


//Тесты на функцию count_int


/**
 * @brief Проверка правильного подсчета цифр в файле
 */
START_TEST(test_pos_1_count_int)
{
    FILE *file = fopen("./unit_tests/data/1.txt", "r");
    size_t size;

    // int rc = count_int(file, &size);
    size = count_int(file);
    ck_assert(size == 4);
    // ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    fclose(file);
}
END_TEST

/**
 * @brief Проверка на то, что файл может быть пустым, то есть функция возвратит 0 
 */
START_TEST(test_neg_1_count_int)
{
    FILE *file = fopen("./unit_tests/data/2.txt", "r");
    size_t size;
    // int rc = count_int(file, &size);
    size = count_int(file);
    ck_assert_uint_eq(size, 0);
    fclose(file);
}
END_TEST

//Отныне не возвращает код ошибок
// START_TEST(test_neg_2_count_int)
// {
//     FILE *file = fopen("./unit_tests/data/3.txt", "r");
//     size_t size;
//     int rc = count_int(file, &size);
//     ck_assert_int_eq(rc, ERR_IO);
//     fclose(file);
// }
// END_TEST



//Тесты на функцию read_into_array


/**
 * @brief Проверка правильного формирования массива на куче
 */
START_TEST(test_pos_1_read_array)
{
    FILE *file = fopen("./unit_tests/data/1.txt", "r");
    int *array = NULL, *pend = NULL;
    // size_t size;
    
    int arr[] = { 1, 2, 3, 4 };
    int rc = read_into_array(file, &array, &pend);

    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    //проверка размера
    ck_assert_uint_eq(pend - array, 4);
    ck_assert_int_eq(array_cmp(array, pend, arr, arr + 4), 0);

    free(array);
    fclose(file);
}
END_TEST


/**
 * @brief Проверка ошибочной ситуации, когда файл пуст
 */
START_TEST(test_neg_1_read_array)
{
    FILE *file = fopen("./unit_tests/data/2.txt", "r");
    int *array = NULL, *pend = NULL;
    int rc = read_into_array(file, &array, &pend);
    ck_assert_int_eq(rc, EMPTY);
    free(array);
    fclose(file);
}
END_TEST


/**
 * @brief Проверка ошибочной ситуации, когда в файле содержится что-то кроме цифр
 */
START_TEST(test_neg_2_read_array)
{
    FILE *file = fopen("./unit_tests/data/3.txt", "r");
    int *array = NULL, *pend = NULL;
    int rc = read_into_array(file, &array, &pend);
    ck_assert_int_eq(rc, ERR_IO);
    free(array);
    fclose(file);
}
END_TEST


//Секция тестов на заголовочный файл fileread
Suite *get_fileread_suite(void)
{
    Suite *suite = suite_create("Fileread tests");

    TCase *tc_pos = tcase_create("Positives");
    tcase_add_test(tc_pos, test_pos_1_count_int);
    tcase_add_test(tc_pos, test_pos_1_read_array);
    suite_add_tcase(suite, tc_pos);

    TCase *tc_neg = tcase_create("Negatives");
    tcase_add_test(tc_neg, test_neg_1_count_int);
    // tcase_add_test(tc_neg, test_neg_2_count_int);
    tcase_add_test(tc_neg, test_neg_1_read_array);
    tcase_add_test(tc_neg, test_neg_2_read_array);
    suite_add_tcase(suite, tc_neg);
    
    return suite;
}

