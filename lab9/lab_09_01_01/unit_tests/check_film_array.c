#include <check.h>
#include <stdio.h>
#include "check_film_array.h"
#include "error.h"

static int cmp_films(const film_t *films1, const film_t *films2, size_t size1, size_t size2)
{
    if (size1 != size2)
        return 1;

    for (size_t i = 0; i < size1; i++)
        if (film_cmp_name(films1 + i, films2 + i))
            return 1;

    return 0;
}


/// Проверка подсчета фильмов
START_TEST(FilmCount)
{
    int rc;
    size_t count = 0;

    film_t film[2] = { { .name = "ABC", .title = "ABC", .year = 111}, { .name = "DEF", .title = "DEF", .year = 222} };
    FILE *file = fopen("unit_tests/data/data.txt", "w");
    if (!file)
    {
        ck_assert_int_eq(0, 1);
    }
    film_array_print(file, film, 2);
    fclose(file);

    FILE *file1 = fopen("unit_tests/data/data.txt", "r");
    if (!file1)
    {
        ck_assert_int_eq(0, 1);
    }
    rc = film_count(file1, &count); 
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    ck_assert_uint_eq(count, 2);

    fclose(file1);
}
END_TEST


/// Проверка считывания и создания массива фильмов
START_TEST(FilmCreatePos)
{
    int rc = EXIT_SUCCESSFUL;
    film_t *films = NULL;

    film_t film[2] = { { .name = "ABC", .title = "ABC", .year = 111}, { .name = "DEF", .title = "DEF", .year = 222} };
    FILE *file = fopen("unit_tests/data/data.txt", "w");
    if (!file)
    {
        ck_assert_int_eq(0, 1);
    }
    film_array_print(file, film, 2);
    fclose(file);

    FILE *file1 = fopen("unit_tests/data/data.txt", "r");
    if (!file1)
    {
        ck_assert_int_eq(0, 1);
    }
    size_t size = 0;
    rc = film_array_create(file1, &films, &size, film_cmp_name);
    ck_assert_int_eq(rc, EXIT_SUCCESSFUL);

    ck_assert_uint_eq(size, 2);
    
    ck_assert_int_eq(cmp_films(films, film, size, 2), 0);

    film_array_free(films, size);
    fclose(file1);
}
END_TEST

START_TEST(FilmCreateNeg)
{
    int rc = EXIT_SUCCESSFUL;
    film_t *films = NULL;

    film_t film[2] = { { .name = "ABC", .title = "ABC", .year = 111}, { .name = "DEF", .title = "DEF", .year = 222} };
    FILE *file = fopen("unit_tests/data/data.txt", "w");
    if (!file)
    {
        ck_assert_int_eq(0, 1);
    }
    film_array_print(file, film, 2);
    fprintf(file, "FGH\n\n"); //запись неполной структуры
    fclose(file);

    FILE *file1 = fopen("unit_tests/data/data.txt", "r");
    if (!file1)
    {
        ck_assert_int_eq(0, 1);
    }
    size_t size = 0;
    
    rc = film_array_create(file1, &films, &size, film_cmp_name);
    ck_assert(rc == CHECK_EOF || rc == ERR_IO);

    film_array_free(films, size);
    fclose(file1);
}
END_TEST

Suite *get_film_array_suite(void)
{
    Suite *suite = suite_create("Film array tests\n");
    
    TCase *pos = tcase_create("Film array pos\n");
    tcase_add_test(pos, FilmCount);
    tcase_add_test(pos, FilmCreatePos);
    

    TCase *neg = tcase_create("Film array neg\n");
    tcase_add_test(neg, FilmCreateNeg);

    suite_add_tcase(suite, pos);
    suite_add_tcase(suite, neg);

    return suite;
}

