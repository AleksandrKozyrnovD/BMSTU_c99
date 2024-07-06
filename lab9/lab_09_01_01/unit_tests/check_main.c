#include <stdlib.h>
#include <check.h>
#include "check_film.h"
#include "check_film_array.h"


int main(void)
{
    Suite *film = get_film_suite();
    Suite *film_array = get_film_array_suite();

    SRunner *srunner = srunner_create(film);
    srunner_add_suite(srunner, film_array);

    srunner_run_all(srunner, CK_VERBOSE); //CK_VERBOSE CK_NORMAL
    srunner_set_fork_status(srunner, CK_NOFORK);
    // srunner_run_all(srunner, CK_NORMAL);

    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return (fails) ? EXIT_FAILURE : EXIT_SUCCESS;
}

