#include "check_list.h"
#include "readstr.h"
#include <assert.h>

//Нахождение подстроки
START_TEST(FindStrPos)
{
    FILE *file1, *file2;

    file1 = fopen("./unit_tests/data/1.txt", "w");
    assert(file1);
    file2 = fopen("./unit_tests/data/2.txt", "w");
    assert(file2);

    fprintf(file1, "aaTESTaaaaaaa\n");
    fprintf(file2, "TEST");
    fclose(file1);
    fclose(file2);
    file1 = fopen("./unit_tests/data/1.txt", "r");
    assert(file1);
    file2 = fopen("./unit_tests/data/2.txt", "r");
    assert(file2);
    
    node_t *head1 = NULL, *head2 = NULL;

    ck_assert_int_eq(EXIT_SUCCESSFUL, readstr(file1, &head1));
    ck_assert_int_eq(EXIT_SUCCESSFUL, readstr(file2, &head2));
    size_t pos = 0;
    int rc = find_str(head1, head2, &pos);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);
    ck_assert_uint_eq(pos, 2);
    
    list_free(head1);
    list_free(head2);
    fclose(file1);
    fclose(file2);
}
END_TEST

//Нахождение подстроки
START_TEST(FindStrNeg)
{
    FILE *file1, *file2;

    file1 = fopen("./unit_tests/data/1.txt", "w");
    assert(file1);
    file2 = fopen("./unit_tests/data/2.txt", "w");
    assert(file2);

    fprintf(file1, "aaTESTaaaaaaa\n");
    fprintf(file2, "TESTTEST");
    fclose(file1);
    fclose(file2);
    file1 = fopen("./unit_tests/data/1.txt", "r");
    assert(file1);
    file2 = fopen("./unit_tests/data/2.txt", "r");
    assert(file2);
    
    node_t *head1 = NULL, *head2 = NULL;

    ck_assert_int_eq(EXIT_SUCCESSFUL, readstr(file1, &head1));
    ck_assert_int_eq(EXIT_SUCCESSFUL, readstr(file2, &head2));
    size_t pos = 0;
    int rc = find_str(head1, head2, &pos);
    ck_assert_int_eq(rc, ERR_EMPTY);
    
    list_free(head1);
    list_free(head2);
    fclose(file1);
    fclose(file2);
}
END_TEST

Suite *get_list_suite(void)
{
    Suite *suite = suite_create("List");

    TCase *pos = tcase_create("pos");
    tcase_add_test(pos, FindStrPos);

    TCase *neg = tcase_create("neg");
    tcase_add_test(neg, FindStrNeg);

    suite_add_tcase(suite, pos);
    suite_add_tcase(suite, neg);

    return suite;
}

