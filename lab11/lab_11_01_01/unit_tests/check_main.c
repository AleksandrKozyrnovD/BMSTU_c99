#include <check.h>
#include <check_test.h>

int main(void)
{
    Suite *test = get_test_suite();
    SRunner *srunner = srunner_create(test);

    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_VERBOSE); //CK_VERBOSE CK_NORMAL
    // srunner_run_all(srunner, CK_NORMAL); //CK_VERBOSE CK_NORMAL

    int fails = srunner_ntests_failed(srunner);

    srunner_free(srunner);

    return (fails) ? 1 : 0;
}
