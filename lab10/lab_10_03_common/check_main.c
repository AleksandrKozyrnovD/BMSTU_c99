#include <check.h>
#include "check_min_max_each.h"
#include "check_insert_find_clear.h"
#include "check_create.h"

int main(void)
{
    Suite *minmaxeach = get_min_max_each();
    Suite *insertfindclear = get_insert_find_clear_suite();
    Suite *create = get_create_suite();

    SRunner *srunner = srunner_create(create);
    srunner_add_suite(srunner, insertfindclear);
    srunner_add_suite(srunner, minmaxeach);

    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_VERBOSE); //CK_VERBOSE CK_NORMAL
    // srunner_run_all(srunner, CK_NORMAL); //CK_VERBOSE CK_NORMAL

    int fails = srunner_ntests_failed(srunner);

    srunner_free(srunner);

    return (fails) ? 1 : 0;
}

