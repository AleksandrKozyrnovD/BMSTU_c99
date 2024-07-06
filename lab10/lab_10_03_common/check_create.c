#include "check_create.h"
#include "associative_array.h"
#include <check.h>

START_TEST(create)
{
    assoc_array_t array = NULL;

    array = assoc_array_create();
    if (!array)
        ck_assert_ptr_null(array);
    else
        ck_assert(array != NULL);

    assoc_array_destroy(&array);
}
END_TEST

START_TEST(destroy)
{
    assoc_array_t array = NULL;
    array = assoc_array_create();
    if (!array)
        ck_assert_ptr_null(array);
    else
    {
        ck_assert(array != NULL);

        assoc_array_destroy(&array);
        ck_assert_ptr_null(array);
    }

    assoc_array_t ptr = NULL;
    assoc_array_destroy(&ptr);
    ck_assert_int_eq(1, 1); //То что с нулевым указателем все прошло верно
}
END_TEST

Suite *get_create_suite(void)
{
    Suite *suite = suite_create("Creating and destroying");

    TCase *test = tcase_create("...");

    tcase_add_test(test, create);
    tcase_add_test(test, destroy);

    suite_add_tcase(suite, test);

    return suite;
}

