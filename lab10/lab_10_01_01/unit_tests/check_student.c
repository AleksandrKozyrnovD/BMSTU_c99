#include <assert.h>
#include <check.h>
#include "check_student.h"

//Чтение студента прошло успешно
START_TEST(ReadPos)
{
    FILE *file = NULL;
    file = fopen("unit_tests/data/data.txt", "w");
    assert(file);
    fprintf(file, "1 a\n");
    fclose(file);
    file = NULL;

    file = fopen("unit_tests/data/data.txt", "r");
    assert(file);
    student_t *student = NULL;
    student_t test = { .name = " a", .mark = 1 };
    errors_t rc = EXIT_SUCCESSFUL;
    rc = student_read_ex(file, &student);
    if (rc == ERR_MEM)
        ck_assert_int_eq(rc, ERR_MEM);
    else
    {
        ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
        ck_assert_int_eq(student_cmp(&test, student), 0);
    }

    student_free(student);
    fclose(file);
}
END_TEST

//Чтение студента прошло НЕуспешно
START_TEST(ReadNeg)
{
    FILE *file = NULL;
    file = fopen("unit_tests/data/data.txt", "w");
    assert(file);
    fclose(file);
    file = NULL;

    file = fopen("unit_tests/data/data.txt", "r");
    assert(file);
    student_t *student = NULL;
    errors_t rc = EXIT_SUCCESSFUL;
    rc = student_read_ex(file, &student);
    ck_assert_int_eq(rc, ERR_IO);
    fclose(file);
}
END_TEST

Suite *get_student_suite(void)
{
    Suite *suite = suite_create("Student test");

    TCase *pos = tcase_create("pos");
    tcase_add_test(pos, ReadPos);

    TCase *neg = tcase_create("neg");
    tcase_add_test(neg, ReadNeg);

    suite_add_tcase(suite, pos);
    suite_add_tcase(suite, neg);

    return suite;
}

