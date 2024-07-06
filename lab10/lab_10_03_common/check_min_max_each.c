#include "check_min_max_each.h"
#include "associative_array.h"
#include <check.h>

static void multval(const char *key, int *num, void *param)
{
    (void) key;
    int *p = param;

    *num *= *p;
}

START_TEST(each)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = assoc_array_create();
    ck_assert(array != NULL);
    
    int param = 2;
    rc = assoc_array_each(array, multval, &param);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    rc = assoc_array_each(array, multval, &param);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    int *num = NULL;

    rc = assoc_array_find(array, "1", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    if (num)
        ck_assert_int_eq(*num, 1 * 2);
    rc = assoc_array_find(array, "2", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    if (num)
        ck_assert_int_eq(*num, 2 * 2);
    rc = assoc_array_find(array, "3", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    if (num)
        ck_assert_int_eq(*num, 3 * 2);

    assoc_array_destroy(&array);
}
END_TEST

START_TEST(min)
{
    int *num = NULL;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = assoc_array_create();
    ck_assert(array != NULL);
    
    rc = assoc_array_min(array, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_min(array, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    if (num)
        ck_assert_int_eq(*num, 1);

    assoc_array_destroy(&array);
}
END_TEST

START_TEST(max)
{
    int *num = NULL;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = assoc_array_create();
    ck_assert(array != NULL);
    
    rc = assoc_array_max(array, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    rc = assoc_array_max(array, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    if (num)
        ck_assert_int_eq(*num, 3);

    rc = assoc_array_insert(array, "30", 30);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_max(array, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    if (num)
        ck_assert_int_eq(*num, 30);


    rc = assoc_array_insert(array, "90", 90);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_max(array, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    if (num)
        ck_assert_int_eq(*num, 90);

    assoc_array_destroy(&array);
}
END_TEST

START_TEST(nullptr)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = assoc_array_create();
    int *num = NULL;
    int number = 2;

    rc = assoc_array_each(array, NULL, &number);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    rc = assoc_array_each(array, multval, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    rc = assoc_array_each(NULL, multval, &number);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    rc = assoc_array_min(array, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    rc = assoc_array_min(NULL, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    rc = assoc_array_max(array, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    rc = assoc_array_max(NULL, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

Suite *get_min_max_each(void)
{
    Suite *suite = suite_create("Min Max Each");

    TCase *pos = tcase_create("pos");

    tcase_add_test(pos, each);
    tcase_add_test(pos, min);
    tcase_add_test(pos, max);

    TCase *neg = tcase_create("neg");
    tcase_add_test(neg, nullptr);

    suite_add_tcase(suite, pos);
    suite_add_tcase(suite, neg);

    return suite;
}

