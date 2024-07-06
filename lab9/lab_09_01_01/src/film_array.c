#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "film.h"
#include "film_array.h"
#include "binarysearch.h"


int film_count(FILE *file, size_t *count)
{
    film_t film = { .title = NULL, .name = NULL, .year = 0 };
    size_t i = 0;
    int rc = EXIT_SUCCESSFUL;

    while (rc == EXIT_SUCCESSFUL)
    {
        rc = film_read_ex(file, &film);
        if (!rc)
        {
            i++;
            film_free_content(&film);
        }
    }

    (*count) = i;
    if (rc != EXIT_SUCCESSFUL && feof(file))
        rc = EXIT_SUCCESSFUL;

    return rc;
}

int film_array_create(FILE *file, film_t **films, size_t *n, comparator_t cmp)
{
    size_t count;
    int rc;

    *films = NULL;
    (*n) = 0;

    rc = film_count(file, &count);

    if (count == 0)
        return ERR_RANGE;
    if (!rc)
    {
        *films = calloc(count, sizeof(**films));
        if (films)
        {
            rewind(file);
            rc = film_array_read(file, *films, count, cmp);
            if (!rc)
                *n = count;
            else
            {
                // film_array_free(*films, count);
                // *films = NULL;
                return rc;
            }
        }
        else
            rc = ERR_MEM;
    }
    return rc;
}

/**
 * @brief Функция вставки в упорядоченный массив структуры
 *
 * @param films Массив структур film_t
 * @param length Размер массива структур с учетом вставляемого элемента
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


void film_array_print(FILE *file, const film_t *films, size_t size)
{
    for (size_t i = 0; i < size; i++)
        film_print(file, films + i);
}

int film_array_read(FILE *file, film_t *films, size_t n, comparator_t cmp)
{
    film_t film;
    int rc = EXIT_SUCCESSFUL;
    size_t curr_lenght = 0;
    for (size_t i = 0; i < n/* + 1 && !rc*/; i++)
    {
        rc = film_read_ex(file, &film);
        if (!rc)
        {
            if (curr_lenght < n)
                insert_sorted(films, ++curr_lenght, &film, cmp);
            else
                return OVERFLOW;
        }
        else
            return ERR_IO;
    }
    if (!feof(file))
        rc = ERR_IO;
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

int film_array_search(const film_t *films, size_t size, film_t *dst, const film_t *what, comparator_t cmp)
{
    int index = binary_search(films, size, what, cmp);
    
    if (index == -1)
        return NOT_FOUND;

    *dst = films[index];

    return EXIT_SUCCESSFUL;
}

void film_array_free(film_t *films, size_t n)
{
    for (size_t i = 0; i < n; i++)
        film_free_content(films + i);

    free(films);
}

