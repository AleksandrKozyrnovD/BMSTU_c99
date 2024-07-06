#include "check_film.h"
#include "error.h"
#include "film.h"
#include <check.h>
#include <stdio.h>


/// Проверка инициализации фильма
START_TEST(FilmInit)
{
    int rc = EXIT_SUCCESSFUL;
    film_t film = { .title = NULL, .name = NULL, .year = 0 };

    rc = film_init_content(&film, "Film1", "Avtor", 2023);

    ck_assert_int_eq(rc, 0);

    ck_assert_str_eq(film.title, "Film1");
    ck_assert_str_eq(film.name, "Avtor");
    ck_assert_int_eq(film.year, 2023);

    film_free_content(&film);
}
END_TEST

/// Проверка копирования фильма
START_TEST(FilmCopy)
{
    int rc = EXIT_SUCCESSFUL;
    film_t film = { .title = NULL, .name = NULL, .year = 0 };
    film_t film1 = { .title = NULL, .name = NULL, .year = 0 };
    rc = film_init_content(&film, "Film1", "Avtor", 2023);

    ck_assert_int_eq(rc, 0);

    ck_assert_str_eq(film.title, "Film1");
    ck_assert_str_eq(film.name, "Avtor");
    ck_assert_int_eq(film.year, 2023);
    rc = film_copy(&film, &film1);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(film_cmp_name(&film1, &film), 0);
    film_free_content(&film);
    film_free_content(&film1);
}
END_TEST

///Проверка считывания фильма
START_TEST(FilmRead_pos)
{
    int rc = EXIT_SUCCESSFUL;
    film_t film = { .title = NULL, .name = NULL, .year = 0 };
    film_t test = { .title = "111", .name = "111", .year = 111 };

    FILE *file = fopen("./unit_tests/data/data.txt", "w");
    film_print(file, &test);
    fclose(file);

    file = fopen("./unit_tests/data/data.txt", "r");
    rc = film_read_ex(file, &film);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(film_cmp_name(&test, &film), 0);

    film_free_content(&film);
    fclose(file);
}
END_TEST

START_TEST(FilmRead_neg1)
{

    int rc = EXIT_SUCCESSFUL;
    film_t film = { .title = NULL, .name = NULL, .year = 0 };

    FILE *file = fopen("./unit_tests/data/data.txt", "w");
    fprintf(file, "111\n111\n");
    /*
        Файл вида:
        111

        111
     */
    fclose(file);

    file = fopen("./unit_tests/data/data.txt", "r");
    rc = film_read_ex(file, &film);
    ck_assert(rc == ERR_IO);

    film_free_content(&film);
    fclose(file);
}
END_TEST

START_TEST(FilmRead_neg2)
{

    int rc = EXIT_SUCCESSFUL;
    film_t film = { .title = NULL, .name = NULL, .year = 0 };
    //
    film_t test = { .title = "111", .name = "111", .year = -111 };
    FILE *file = fopen("./unit_tests/data/data.txt", "w");
    film_print(file, &test);
    fclose(file);
    file = fopen("./unit_tests/data/data.txt", "r");
    //
    rc = film_read_ex(file, &film);
    ck_assert(rc != EXIT_SUCCESSFUL);
    //
    film_free_content(&film);
    fclose(file);
}
END_TEST


Suite *get_film_suite(void)
{
    Suite *suite = suite_create("Film test\n");
    
    TCase *pos = tcase_create("Film positive\n");
    tcase_add_test(pos, FilmInit);
    tcase_add_test(pos, FilmRead_pos);
    tcase_add_test(pos, FilmCopy);


    TCase *neg = tcase_create("Film negative\n");
    tcase_add_test(neg, FilmRead_neg1);
    tcase_add_test(neg, FilmRead_neg2);

    suite_add_tcase(suite, pos);
    suite_add_tcase(suite, neg);

    return suite;
}

