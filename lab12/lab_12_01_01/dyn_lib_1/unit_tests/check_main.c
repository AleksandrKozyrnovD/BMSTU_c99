#include "check_filter.h"
#include "check_sort.h"
#include "check_fileread.h"
#include <stdlib.h>


int main(void)
{
    Suite *fileread = get_fileread_suite();
    Suite *filter = get_filter_suite();
    Suite *sort = get_sort_suite();

    SRunner *srunner = srunner_create(fileread);
    srunner_add_suite(srunner, filter);
    srunner_add_suite(srunner, sort);

    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_VERBOSE); //CK_VERBOSE CK_NORMAL
    // srunner_run_all(srunner, CK_NORMAL); //CK_VERBOSE CK_NORMAL

    int fails = srunner_ntests_failed(srunner);

    srunner_free(srunner);

    return (fails) ? EXIT_FAILURE : EXIT_SUCCESS;
}
