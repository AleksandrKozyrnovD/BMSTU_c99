#include <assert.h>
#include <string.h>
#include "error.h"
#include "film.h"
#include "film_array.h"
#include "binarysearch.h"

// /**
//  * @brief Функция вставки в упорядоченный массив структуры
//  *
//  * @param films Массив структур film_t
//  * @param length Размер массива структур
//  * @param what Структура, которая вставляется
//  */
// static void insert_sorted_year(film_t *films, size_t length, const film_t *what)
// {
//     assert((length != 0));
//
//     size_t i = length - 1;
//     for (; i != 0 && (film_cmp_year(films + i - 1, what) > 0); --i)
//     {
//         films[i] = films[i - 1];
//     }
//     // for (; i != 0 && films[i - 1].year == what->year && film_cmp_title(films + i - 1, what) > 0; --i)
//     // {
//     //     films[i] = films[i - 1];
//     // }
//     // for (; i != 0 && films[i - 1].year == what->year && film_cmp_title(films + i - 1, what) == 0 && film_cmp_name(films + i - 1, what) > 0; --i)
//     // {
//     //     films[i] = films[i - 1];
//     // }
//     films[i] = *what;
// }
//
// /**
//  * @brief Функция вставки в упорядоченный массив структуры
//  *
//  * @param films Массив структур film_t
//  * @param length Размер массива структур
//  * @param what Структура, которая вставляется
//  */
// static void insert_sorted_name(film_t *films, size_t length, const film_t *what)
// {
//     assert((length != 0));
//
//     size_t i = length - 1;
//     // for (; i != 0 && films[i - 1].year > what->year; --i)
//     // for (; i != 0 && film_cmp_name(films + i - 1, what) > 0; --i)
//     // {
//     //     films[i] = films[i - 1];
//     // }
//     for (; i != 0 && film_cmp_name(films + i - 1, what) > 0; --i)
//     {
//         films[i] = films[i - 1];
//     }
//     // for (; i != 0 && film_cmp_name(films + i - 1, what) == 0 && films[i - 1].year > what->year; --i)
//     // {
//     //     films[i] = films[i - 1];
//     // }
//     // for (; i != 0 && films[i - 1].year == what->year && film_cmp_title(films + i - 1, what) > 0 && film_cmp_name(films + i - 1, what) == 0; --i)
//     // {
//     //     films[i] = films[i - 1];
//     // }
//     films[i] = *what;
// }
//
/**
 * @brief Функция вставки в упорядоченный массив структуры
 *
 * @param films Массив структур film_t
 * @param length Размер массива структур
 * @param what Структура, которая вставляется
 */
// static void insert_sorted_title(film_t *films, size_t lenght, const film_t *what)
// {
//     assert((lenght != 0));
//
//     size_t i = lenght - 1;
//     // for (; i != 0 && films[i - 1].year > what->year; --i)
//     // for (; i != 0 && film_cmp_title(films + i - 1, what) > 0; --i)
//     // {
//     //     films[i] = films[i - 1];
//     // }
//     for (; i != 0 && film_cmp_title(films + i - 1, what) > 0; --i)
//     {
//         films[i] = films[i - 1];
//     }
//     // for (; i != 0 && film_cmp_title(films + i - 1, what) == 0 && film_cmp_name(films + i - 1, what) > 0; --i)
//     // {
//     //     films[i] = films[i - 1];
//     // }
//     // for (; i != 0 && films[i - 1].year > what->year && film_cmp_title(films + i - 1, what) == 0 && film_cmp_name(films + i - 1, what) == 0; --i)
//     // {
//     //     films[i] = films[i - 1];
//     // }
//     films[i] = *what;
// }

/**
 * @brief Функция вставки в упорядоченный массив структуры
 *
 * @param films Массив структур film_t
 * @param length Размер массива структур
 * @param what Структура, которая вставляется
 * @param cmp Сравнитель для структур
 */
static void insert_sorted(film_t *films, size_t lenght, const film_t *what, comparator_t cmp)
{
    assert((lenght != 0));

    size_t i = lenght - 1;
    for (; i != 0 && cmp(films + i - 1, what) > 0; --i)
    {
        films[i] = films[i - 1];
    }
    films[i] = *what;
}

// void film_array_insert(film_t *films, size_t *size, const film_t *what, comparator_t cmp)
// {
//     (*size)++;
//     insert_sorted(films, *size, what, cmp);
// }

void film_array_print(FILE *file, const film_t *films, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        film_print(file, films + i);
        // printf("\n");
    }
    // film_print(file, films + size - 1);
}

int film_array_read(FILE *file, film_t *films, size_t *size, size_t n_max, comparator_t cmp)
{
    *size = 0;
    film_t film;
    int rc = EXIT_SUCCESSFUL;
    // while (rc == EXIT_SUCCESSFUL)
    // {
    //     rc = film_read(file, &film);
    //     if (rc != EXIT_SUCCESSFUL && feof(file))
    //     {
    //         break;
    //     }
    //     if (rc != EXIT_SUCCESSFUL)
    //         break;
    //     // printf("%zu :: %zu\n", *size, n_max);
    //     if (*size < n_max)
    //         film_array_insert(films, size, &film, choice);
    //     else
    //         return OVERFLOW;
    // }
    
    rc = film_read(file, &film);
    while (rc == EXIT_SUCCESSFUL && *size < n_max)
    {
        // film_array_insert(films, size, &film, cmp);
        (*size)++;
        insert_sorted(films, *size, &film, cmp);
        rc = film_read(file, &film);
    }

    // printf("Rc = %d, size = %zu\n", rc, *size);
    if (feof(file))
        rc = EXIT_SUCCESSFUL;

    // printf("Rc = %d, size = %zu\n", rc, *size);
    if (*size == 0)
        rc = EMPTY;

    // printf("Rc = %d, size = %zu\n", rc, *size);
    if (*size == n_max)
    {
        rc = film_read(file, &film);
        // printf("Rc = %d, size = %zu\n", rc, *size);
        if (rc == EXIT_SUCCESSFUL || rc == CHECK_EOF)
            return OVERFLOW;
        rc = EXIT_SUCCESSFUL;
    }
    
    // printf("Rc = %d, size = %zu\n", rc, *size);
    return rc;
}

int get_choice_by_name(const char *name)
{
    if (strcmp("title", name) == 0)
        return TITLE_CHOICE;
    else if (strcmp("name", name) == 0)
        return NAME_CHOICE;
    else if (strcmp("year", name) == 0)
        return YEAR_CHOICE;
    else
        return ERR_CHOICE;
}

// int film_array_search_title(const film_t *films, size_t size, film_t *film, const char *title)
// {
//     int index = binary_search_title(films, size, title);
//
//     if (index == -1)
//         return NOT_FOUND;
//     *film = films[index];
//
//     return EXIT_SUCCESSFUL;
// }
//
// int film_array_search_name(const film_t *films, size_t size, film_t *film, const char *name)
// {
//     int index = binary_search_name(films, size, name);
//
//     if (index == -1)
//         return NOT_FOUND;
//     *film = films[index];
//
//     return EXIT_SUCCESSFUL;
// }
//
// int film_array_search_year(const film_t *films, size_t size, film_t *film, size_t year)
// {
//     int index = binary_search_year(films, size, year);
//
//     if (index == -1)
//         return NOT_FOUND;
//     *film = films[index];
//
//     return EXIT_SUCCESSFUL;
// }

int film_array_search(const film_t *films, size_t size, film_t *dst, const film_t *what, comparator_t cmp)
{
    int index = binary_search(films, size, what, cmp);
    
    if (index == -1)
        return NOT_FOUND;

    *dst = films[index];

    return EXIT_SUCCESSFUL;
}
