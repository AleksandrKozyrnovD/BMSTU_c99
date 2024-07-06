#include "check_insert_find_clear.h"
#include <check.h>

START_TEST(insertpos)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = assoc_array_create();
    ck_assert(array != NULL);

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "a", 4);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "b", 5);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "c", 6);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "d", 7);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "e", 8);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "f", 9);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "g", 10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "h", 11);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "j", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "k", 13);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&array);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(insertneg)
{
    assoc_array_t array = NULL;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    array = assoc_array_create();
    ck_assert(array != NULL);

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&array);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(findpos)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = assoc_array_create();

    int *num = NULL;
    ck_assert(array != NULL);

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    rc = assoc_array_find(array, "2", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert(num != NULL);
    if (num)
        ck_assert_int_eq(*num, 2);

    rc = assoc_array_find(array, "3", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert(num != NULL);
    if (num)
        ck_assert_int_eq(*num, 3);

    rc = assoc_array_find(array, "1", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert(num != NULL);
    if (num)
        ck_assert_int_eq(*num, 1);

    assoc_array_destroy(&array);
}
END_TEST

START_TEST(findneg)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = assoc_array_create();

    int *num = NULL;
    ck_assert(array != NULL);

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    rc = assoc_array_find(array, "4", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(array, "5", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(array, "6", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST

START_TEST(clear)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = assoc_array_create();

    int *num = NULL;
    ck_assert(array != NULL);

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    rc = assoc_array_clear(array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "1", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(array, "2", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(array, "3", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST

START_TEST(nullptrneg)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    assoc_array_t array = NULL;
    int *num = NULL;

    rc = assoc_array_insert(array, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    rc = assoc_array_clear(array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    rc = assoc_array_find(array, "1", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

Suite *get_insert_find_clear_suite(void)
{
    Suite *suite = suite_create("Insert find clear tests");
    
    TCase *pos = tcase_create("Pos");

    tcase_add_test(pos, insertpos);
    tcase_add_test(pos, findpos);
    tcase_add_test(pos, clear);
    
    TCase *neg = tcase_create("Neg");
    tcase_add_test(neg, insertneg);
    tcase_add_test(neg, findneg);
    tcase_add_test(neg, nullptrneg);
    
    suite_add_tcase(suite, pos);
    suite_add_tcase(suite, neg);

    return suite;
}

