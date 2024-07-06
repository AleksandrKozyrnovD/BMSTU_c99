#include "check_sort.h"
#include <check.h>
#include <string.h>

/**
 * @brief Сравнитель массивов
 *
 * @param[in] pbeg1 Указатель на начало первого
 * @param[in] pend1 Указатель на конец первого
 * @param[in] pbeg2 Указатель на начало второго
 * @param[in] pend2 Указатель на конец второго
 * @return Разница
 */
static int array_cmp(const void *pbeg1, const void *pend1, const void *pbeg2, const void *pend2, size_t size, int (*cmp)(const void *l, const void *r))
{
    //Проверка на равенство длин
    const char *beg1 = pbeg1;
    const char *beg2 = pbeg2;
    const char *end1 = pend1;
    const char *end2 = pend2;

    int cmp_score = (end1 - beg1) - (end2 - beg2);
    if (cmp_score)
        return cmp_score;
    
    //Проверка на равенство элементов
    const char *pcur1 = pbeg1, *pcur2 = pbeg2;
    for (; pcur1 < end1; pcur1 += size, pcur2 += size)
    {
        cmp_score = cmp(pcur1, pcur2);
        if (cmp_score)
            return cmp_score;
    }

    return cmp_score;
}

static int cmp_int(const void *l, const void *r)
{
    return *(int *) l - *(int *) r;
}

typedef struct test_t
{
    int a;
    int b;
} test_t;

//Сравнение отношений
static int cmp_struct(const void *l, const void *r)
{
    const test_t *left = l;
    const test_t *right = r;

    return (left->a / left->b) - (right->a / right->b);
}

/**
 * @brief Проверка сортировки на 1м элементе
 */
START_TEST(test_1_sort)
{
    // printf("1\n");

    int a[] = { 1 };
    int b[] = { 1 };
    mysort(a, sizeof(a) / sizeof(*a), sizeof(int), cmp_int);
    ck_assert_uint_eq(sizeof(a) / sizeof(*a), 1);
    // ck_assert_int_eq(memcmp(a, b, sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b)), 0);
    int cmp_score = array_cmp(a, a + sizeof(a) / sizeof(*a), b, b + sizeof(b) / sizeof(*b), sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_score, 0);


}
END_TEST

/**
 * @brief Проверка сортировки на 2х возврастающих элементах
 */
START_TEST(test_2_sort)
{
    // printf("2\n");
    int a[] = { 1, 2 };
    int b[] = { 1, 2 };
    mysort(a, sizeof(a) / sizeof(*a), sizeof(int), cmp_int);
    ck_assert_uint_eq(sizeof(a) / sizeof(*a), 2);
    // ck_assert_int_eq(memcmp(a, b, sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b)), 0);
    int cmp_score = array_cmp(a, a + sizeof(a) / sizeof(*a), b, b + sizeof(b) / sizeof(*b), sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_score, 0);
}
END_TEST

/**
 * @brief Проверка сортировки на 2х убывающих элементах
 */
START_TEST(test_3_sort)
{
    // printf("3\n");
    int a[] = { 2, 1 };
    int b[] = { 1, 2 };
    mysort(a, sizeof(a) / sizeof(*a), sizeof(int), cmp_int);
    ck_assert_uint_eq(sizeof(a) / sizeof(*a), 2);
    // ck_assert_int_eq(memcmp(a, b, sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b)), 0);
    int cmp_score = array_cmp(a, a + sizeof(a) / sizeof(*a), b, b + sizeof(b) / sizeof(*b), sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_score, 0);
}
END_TEST

/**
 * @brief Проверка сортировки на многочисленных возврастающих элементах
 */
START_TEST(test_4_sort)
{
    // printf("4\n");
    int a[] = { 1, 2, 3, 4 };
    int b[] = { 1, 2, 3, 4 };
    mysort(a, sizeof(a) / sizeof(*a), sizeof(int), cmp_int);
    ck_assert_uint_eq(sizeof(a) / sizeof(*a), 4);
    // ck_assert_int_eq(memcmp(a, b, sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b)), 0);
    int cmp_score = array_cmp(a, a + sizeof(a) / sizeof(*a), b, b + sizeof(b) / sizeof(*b), sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_score, 0);
}
END_TEST

/**
 * @brief Проверка сортировки на многочисленных убывающих элементах
 */
START_TEST(test_5_sort)
{
    // printf("5\n");
    int a[] = { 4, 3, 2, 1 };
    int b[] = { 1, 2, 3, 4 };
    mysort(a, sizeof(a) / sizeof(*a), sizeof(int), cmp_int);
    ck_assert_uint_eq(sizeof(a) / sizeof(*a), 4);
    // ck_assert_int_eq(memcmp(a, b, sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b)), 0);
    int cmp_score = array_cmp(a, a + sizeof(a) / sizeof(*a), b, b + sizeof(b) / sizeof(*b), sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_score, 0);
}
END_TEST

/**
 * @brief Проверка сортировки на случайном массиве без повторений
 */
START_TEST(test_6_sort)
{
    // printf("6\n");
    int a[] = { 1, 5, 3, 4, 2 };
    int b[] = { 1, 2, 3, 4, 5 };
    mysort(a, sizeof(a) / sizeof(*a), sizeof(int), cmp_int);
    ck_assert_uint_eq(sizeof(a) / sizeof(*a), 5);
    // ck_assert_int_eq(memcmp(a, b, sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b)), 0);
    int cmp_score = array_cmp(a, a + sizeof(a) / sizeof(*a), b, b + sizeof(b) / sizeof(*b), sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_score, 0);
}
END_TEST

/**
 * @brief Проверка сортировки на случайном массиве с повторениями
 */
START_TEST(test_7_sort)
{
    // printf("7\n");
    int a[] = { 1, 5, 3, 4, 2, 2, 3, 1, 4, 5 };
    int b[] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
    mysort(a, sizeof(a) / sizeof(*a), sizeof(int), cmp_int);
    ck_assert_uint_eq(sizeof(a) / sizeof(*a), 10);
    // ck_assert_int_eq(memcmp(a, b, sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b)), 0);
    int cmp_score = array_cmp(a, a + sizeof(a) / sizeof(*a), b, b + sizeof(b) / sizeof(*b), sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_score, 0);
}
END_TEST

// START_TEST(test_8_sort)
// {
//     printf("8\n");
//     char *a[] = { "C", "B", "A" };
//
//     mysort(a, sizeof(a) / sizeof(*a), sizeof(int), cmp_str);
//     ck_assert_int_eq(strcmp(a[0], "A"), 0);
//     ck_assert_int_eq(strcmp(a[1], "B"), 0);
//     ck_assert_int_eq(strcmp(a[2], "C"), 0);
// }
// END_TEST

/**
 * @brief Проверка работоспособности на структурах
 */
START_TEST(test_9_sort)
{
    // printf("9\n");
    test_t i, j, k;
    i = (test_t) { 1, 1 };
    j = (test_t) { 6, 2 };
    k = (test_t) { 10, 2 };
    test_t a[] = { k, j, i };
    test_t b[] = { { 1, 1 }, { 6, 2 }, { 10, 2 } };
    mysort(a, sizeof(a) / sizeof(*a), sizeof(test_t), cmp_struct);
    // printf("%d,%d :: %d,%d :: %d,%d\n", k.a, k.b,
    //                                     a[1].a, a[1].b,
    //                                     a[2].a, a[2].b);
    ck_assert_int_eq(cmp_struct(a + 0, &i), 0);
    ck_assert_int_eq(cmp_struct(a + 1, &j), 0);
    ck_assert_int_eq(cmp_struct(a + 2, &k), 0);
    ck_assert_int_eq(memcmp(a, b, sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b)), 0);
    int cmp_score = array_cmp(a, a + sizeof(a) / sizeof(*a), b, b + sizeof(b) / sizeof(*b), sizeof(test_t), cmp_struct);
    ck_assert_int_eq(cmp_score, 0);
}
END_TEST

/**
 * @brief Проверка, что при размере 0 ничего страшного не произойдет
 */
START_TEST(test_10_sort)
{
    // printf("10\n");
    int a[] = { 1 }; //Чтобы не ругался на пустой массив
    mysort(a, 0, sizeof(int), cmp_int); //ВНИМАНИЕ: размер указан как 0. Сделано, чтобы показать, что ошибки не будет
    // ck_assert_int_eq(sizeof(a) / sizeof(*a), 0);
    ck_assert_int_eq(0, 0); 
}
END_TEST


Suite *get_sort_suite(void)
{
    Suite *suite = suite_create("Sort tests");

    TCase *tc = tcase_create("Sortings");
    tcase_add_test(tc, test_1_sort);
    tcase_add_test(tc, test_2_sort);
    tcase_add_test(tc, test_3_sort);
    tcase_add_test(tc, test_4_sort);
    tcase_add_test(tc, test_5_sort);
    tcase_add_test(tc, test_6_sort);
    tcase_add_test(tc, test_7_sort);
    // tcase_add_test(tc, test_8_sort);
    tcase_add_test(tc, test_9_sort);
    tcase_add_test(tc, test_10_sort);
    suite_add_tcase(suite, tc);

    return suite;
}

