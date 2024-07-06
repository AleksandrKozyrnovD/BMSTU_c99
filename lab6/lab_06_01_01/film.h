#ifndef FILM_H__
#define FILM_H__


#include <stdio.h>
#include "error.h"

#define TITLE_LEN 25
#define NAME_LEN 25


typedef struct
{
    char title[TITLE_LEN + 1];
    char name[NAME_LEN + 1];
    int year;
} film_t;

typedef int (*comparator_t)(const film_t *, const film_t *);

/**
 * @brief Функция чтения из потока ввода FILE структуры film_t
 *
 * @param[in] file поток ввода
 * @param[out] film указатель на структуру
 * @return код ошибки
 */
int film_read(FILE *file, film_t *film);

/**
 * @brief Функция вывода в поток вывода FILE структуры film_t
 *
 * @param[in] file поток вывода
 * @param[in] film указатель на структуру
 */
void film_print(FILE *file, const film_t *film);

/**
 * @brief Функция сравнения структуры film_t по полю
 *
 * @param[in] left указатель на левую структуру
 * @param[in] right указатель на правую структуру
 * @return Целое число сравнения
 */
int film_cmp_title(const film_t *left, const film_t *right);

/**
 * @brief Функция сравнения структуры film_t по полю
 *
 * @param[in] left указатель на левую структуру
 * @param[in] right указатель на правую структуру
 * @return Целое число сравнения
 */
int film_cmp_name(const film_t *left, const film_t *right);

/**
 * @brief Функция сравнения структуры film_t по полю
 *
 * @param[in] left указатель на левую структуру
 * @param[in] right указатель на правую структуру
 * @return Целое число сравнения
 */
int film_cmp_year(const film_t *left, const film_t *right);


/**
 * @brief Функция сравнения структуры film_t по полю (только на равенство поля)
 *
 * @param[in] left указатель на левую структуру
 * @param[in] right указатель на правую структуру
 * @return Целое число сравнения
 */
int film_cmp_title_explicit(const film_t *left, const film_t *right);

/**
 * @brief Функция сравнения структуры film_t по полюю (только на равенство поля)
 *
 * @param[in] left указатель на левую структуру
 * @param[in] right указатель на правую структуру
 * @return Целое число сравнения
 */
int film_cmp_name_explicit(const film_t *left, const film_t *right);

/**
 * @brief Функция сравнения структуры film_t по полюю (только на равенство поля)
 *
 * @param[in] left указатель на левую структуру
 * @param[in] right указатель на правую структуру
 * @return Целое число сравнения
 */
int film_cmp_year_explicit(const film_t *left, const film_t *right);

#endif
