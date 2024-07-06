#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "error.h"
#include "film_array.h"

/**
 * @brief Функция для проверки ввода целого числа (Является ли данная строка числом?)
 *
 * @param[in] buffer Строка
 * @return Правда или ложь
 */
static int check_int(const char *buffer)
{
    int rc = EXIT_SUCCESSFUL;

    for (int i = 0; buffer[i] != 0 && rc == EXIT_SUCCESSFUL; i++)
    {
        if (!isdigit(buffer[i]))
            rc = ERR_ARGS;
    }
    
    return rc;
}

/**
 * @brief Функция получения нестрогого сравнителя по выбору
 *
 * @param choice Выбор (надо было бы enum ввести, но уже поздно)
 * @return Указатель на функцию
 */
static comparator_t get_cmp(int choice)
{
    switch (choice)
    {
        case TITLE_CHOICE:
            return film_cmp_title;
        case NAME_CHOICE:
            return film_cmp_name;
        case YEAR_CHOICE:
            return film_cmp_year;
        default:
            return NULL;
    }
}

/**
 * @brief Функция получения строгого сравнителя по выбору
 *
 * @param choice Выбор (надо было бы enum ввести, но уже поздно)
 * @return Указатель на функцию
 */
static comparator_t get_cmp_explicit(int choice)
{
    switch (choice)
    {
        case TITLE_CHOICE:
            return film_cmp_title_explicit;
        case NAME_CHOICE:
            return film_cmp_name_explicit;
        case YEAR_CHOICE:
            return film_cmp_year_explicit;
        default:
            return NULL;
    }
}

/*
 * Usage:
 *  ./app.exe FILE FIELD KEY
 *
 *  FIELD = [title, name, year]
 *  KEY = what we want to find
 * */
int main(int argc, char **argv)
{
    film_t *films = NULL;
    int choice, rc = EXIT_SUCCESSFUL;
    comparator_t cmp;
    size_t size = 0;

    if (argc < 2 || argc > 4)
        return ERR_ARGS;

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
        return ERR_ARGS;

    choice = get_choice_by_name(argv[2]);
    if (argc == 3)
        cmp = get_cmp(choice);
    else
        cmp = get_cmp_explicit(choice);
    
    if (!cmp)
        rc = ERR_CHOICE;

    if (!rc)
    {
        rc = film_array_create(file, &films, &size, cmp);
        if (!rc)
        {
            if (argc == 3)
            {
                if (!rc)
                    film_array_print(stdout, films, size);
            }
            else
            {
                film_t film = { .title = NULL, .name = NULL, .year = 0 };
                film_t what = { .title = NULL, .name = NULL, .year = 0 };
                switch (choice)
                {
                    case TITLE_CHOICE:
                        what.title = strdup(argv[3]);
                        if (!what.title)
                        {
                            film_free_content(&what);
                            film_array_free(films, size);
                            films = NULL;
                            size = 0;
                            return ERR_ARGS;
                        }
                        break;
                    case NAME_CHOICE:
                        what.name = strdup(argv[3]);
                        if (!what.name)
                        {
                            film_free_content(&what);
                            film_array_free(films, size);
                            films = NULL;
                            size = 0;
                            return ERR_ARGS;
                        }
                        break;
                    case YEAR_CHOICE:
                        if (check_int(argv[3]) != EXIT_SUCCESSFUL)
                        {
                            film_array_free(films, size);
                            films = NULL;
                            size = 0;
                            return ERR_ARGS;
                        }
                        what.year = atoi(argv[3]);
                        break;
                }

                rc = film_array_search(films, size, &film, &what, cmp);
                film_free_content(&what);
                if (rc == EXIT_SUCCESSFUL)
                    film_print(stdout, &film);
                else if (rc == NOT_FOUND)
                {
                    film_array_free(films, size);
                    size = 0;
                    films = NULL;
                    printf("Not found\n");
                    rc = EXIT_SUCCESSFUL;
                }
            }
        }
    }

    fclose(file);
    film_array_free(films, size);

    return rc;
}

