#include <assert.h>
#include <check.h>
#include "check_filereadd.h"

static int cmp_buf(const student_t *left, size_t size_left, const student_t *right, size_t size_right)
{
    if (size_left != size_right)
        return 1;

    for (size_t i = 0; i < size_left; i++)
        if (student_cmp(left + i, right + i))
            return 1;

    return 0;
}

//Создание буфера прошло успешно
START_TEST(CreateBufferPos)
{
    FILE *file = fopen("unit_tests/data/data.txt", "w");
    assert(file);
    fprintf(file, "1 a\n");
    fprintf(file, "2 b\n");
    fprintf(file, "3 c\n");
    fclose(file);
    file = NULL;
    
    student_t *buffer = NULL;
    size_t size = 0;
    student_t test[3] = { { .name = " a", .mark = 1 }, { .name = " b", .mark = 2 }, { .name = " c", .mark = 3 } };
    errors_t rc = EXIT_SUCCESSFUL;
    file = fopen("unit_tests/data/data.txt", "r");
    assert(file);
    rc = create_buffer(file, &buffer, &size);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_int_eq(cmp_buf(buffer, size, test, 3), 0);
    buffer_free(buffer, size);
    fclose(file);
}
END_TEST

//Создание буфера прошло НЕуспешно
START_TEST(CreateBufferNeg)
{
    FILE *file = fopen("unit_tests/data/data.txt", "w");
    assert(file);
    fclose(file);
    file = NULL;
    
    student_t *buffer = NULL;
    size_t size = 0;
    errors_t rc = EXIT_SUCCESSFUL;
    file = fopen("unit_tests/data/data.txt", "r");
    assert(file);
    rc = create_buffer(file, &buffer, &size);
    ck_assert_int_eq(rc, ERR_EMPTY);
    fclose(file);
}
END_TEST


//Считывание в лист прошло успешно
START_TEST(ReadListPos)
{
    FILE *file = fopen("unit_tests/data/data.txt", "w");
    assert(file);
    fprintf(file, "1 a\n");
    fprintf(file, "2 b\n");
    fprintf(file, "3 c\n");
    fclose(file);
    file = NULL;
    
    student_t *buffer = NULL;
    size_t size = 0;
    student_t test[3] = { { .name = " a", .mark = 1 }, { .name = " b", .mark = 2 }, { .name = " c", .mark = 3 } };
    errors_t rc = EXIT_SUCCESSFUL;
    file = fopen("unit_tests/data/data.txt", "r");
    assert(file);
    rc = create_buffer(file, &buffer, &size);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_int_eq(cmp_buf(buffer, size, test, 3), 0);

    node_t *head = NULL;

    rc = read_into_list(buffer, size, &head);
    if (rc == ERR_MEM)
        ck_assert_int_eq(rc, ERR_MEM);
    else
        ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    node_t *tmp = head;
    size_t i = 0;
    while (tmp)
    {
        ck_assert_int_eq(student_cmp(tmp->data, buffer + i), 0);
        tmp = tmp->next;
        i++;
    }
    ck_assert_uint_eq(i, size);
    
    list_free(head);
    buffer_free(buffer, size);
    fclose(file);
}
END_TEST


Suite *get_fileread_suitee(void)
{
    Suite *suite = suite_create("Fileread tests");

    TCase *pos = tcase_create("Pos");
    tcase_add_test(pos, CreateBufferPos);
    tcase_add_test(pos, ReadListPos);
    
    TCase *neg = tcase_create("Neg");
    tcase_add_test(neg, CreateBufferNeg);

    suite_add_tcase(suite, pos);
    suite_add_tcase(suite, neg);

    return suite;
}

