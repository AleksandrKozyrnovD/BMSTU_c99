#include <check.h>
#include "check_filereadd.h"
#include "check_student.h"
#include "check_list.h"


int main(void)
{
    
    Suite *list = get_list_suite();
    Suite *student = get_student_suite();
    Suite *fileread = get_fileread_suitee();

    SRunner *srunner = srunner_create(list);
    srunner_add_suite(srunner, student);
    srunner_add_suite(srunner, fileread);

    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_VERBOSE); //CK_VERBOSE CK_NORMAL
    // srunner_run_all(srunner, CK_NORMAL); //CK_VERBOSE CK_NORMAL

    int fails = srunner_ntests_failed(srunner);

    srunner_free(srunner);

    return (fails) ? 1 : 0;
}

