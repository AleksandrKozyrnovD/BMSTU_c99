#include <stdlib.h>
#include <check.h>
#include "check_matrix.h"
#include "check_matrix_alloc.h"
#include "check_matrix_operations.h"


int main(void)
{
    Suite *matrix = get_matrix_suite();
    Suite *matrix_allocc = get_matrix_alloc_suite();
    Suite *matrix_operationss = get_matrix_operations_suite();

    SRunner *srunner = srunner_create(matrix);
    srunner_add_suite(srunner, matrix_allocc);
    srunner_add_suite(srunner, matrix_operationss);

    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_VERBOSE); //CK_VERBOSE CK_NORMAL
    // srunner_run_all(srunner, CK_NORMAL); //CK_VERBOSE CK_NORMAL

    int fails = srunner_ntests_failed(srunner);

    srunner_free(srunner);

    return (fails) ? EXIT_FAILURE : EXIT_SUCCESS;
}

