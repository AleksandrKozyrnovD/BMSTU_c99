#include "check_fileread.h"
#include "fileread.h"
#include <assert.h>
#include <check.h>
#include <stdio.h>
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

/**
 * @brief Функция печати массива в файл
 * 
 * @param file Файл
 * @param beg Начало массива
 * @param end Конец массива
 */
static void print_array(FILE *file, int *beg, int *end)
{
    while (beg < end)
    {
        fprintf(file, "%d\n", *beg);
        beg++;
    }
}

//Тесты на функцию count_int


/**
 * @brief Проверка правильного подсчета цифр в файле
 */
START_TEST(test_pos_1_count_int)
{
    FILE *file = fopen("./unit_tests/data/1.txt", "w");
    fprintf(file, "1\n2\n3\n4\n");
    fclose(file);

    file = fopen("./unit_tests/data/1.txt", "r");
    assert(file);
    size_t size;

    size = count_int(file);
    ck_assert(size == 4);
    fclose(file);
}
END_TEST

/**
 * @brief Проверка на то, что файл может быть пустым, то есть функция возвратит 0 
 */
START_TEST(test_neg_1_count_int)
{
    FILE *file = fopen("./unit_tests/data/2.txt", "w");
    fclose(file);

    file = fopen("./unit_tests/data/2.txt", "r");
    size_t size;
    // int rc = count_int(file, &size);
    size = count_int(file);
    ck_assert_uint_eq(size, 0);
    fclose(file);
}
END_TEST

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
    int buf[] = { 1, 2, 3, 4 };
    FILE *file = fopen("./unit_tests/data/1.txt", "w");
    print_array(file, buf, buf + 4);
    fclose(file);

    file = fopen("./unit_tests/data/1.txt", "r");
    int *array = NULL, *arrayend = NULL;

    size_t size = count_int(file);
    rewind(file);
    ck_assert_uint_eq(size, 4);
    array = malloc(size * sizeof(int));
    assert(array);
    arrayend = array + size;

    int rc = fill_array(file, array, arrayend);

    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_array_eq(array, arrayend, buf, buf + 4);

    free(array);
    fclose(file);
}
END_TEST

/**
 * @brief Проверка ошибочной ситуации, когда в файле содержится что-то кроме цифр
 */
START_TEST(test_neg_2_read_array)
{
    FILE *file = fopen("./unit_tests/data/3.txt", "w");
    fprintf(file, "1\n2\na\n4\n");
    fclose(file);
    file = fopen("./unit_tests/data/3.txt", "r");
    size_t size = count_int(file);
    int *array = malloc(size * sizeof(int));
    assert(array);
    int *arrayend = array + size;
    int rc = fill_array(file, array, arrayend);
    ck_assert_int_eq(rc, ERR_IO);

    // int rc = read_into_array(file, &array, &size);
    // ck_assert_int_eq(rc, ERR_IO);
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
    // tcase_add_test(tc_neg, test_neg_1_read_array);
    tcase_add_test(tc_neg, test_neg_2_read_array);
    suite_add_tcase(suite, tc_neg);
    
    return suite;
}

