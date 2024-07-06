#ifndef FILM_H__
#define FILM_H__


#include <stdio.h>
#include "error.h"


typedef struct
{
    char *title, *name;
    int year;
} film_t;

typedef int (*comparator_t)(const film_t *, const film_t *);

/**
 * @brief Функция инициализации содержимого структуры
 *
 * @param[out] film Указатель на структуру
 * @param[in] title Название фильма
 * @param[in] name Имя автора
 * @param[in] year Год издания
 * @return Код ошибки
 */
int film_init_content(film_t *film, const char *title, const char *name, int year);

/**
 * @brief Функция глубокого копирования фильма
 *
 * @param[in] src Исходный фильм
 * @param[out] dst Скопированный фильм
 * @return Код ошибки
 */
int film_copy(const film_t *src, film_t *dst);

/**
 * @brief Функция освобождения содержимого
 *
 * @param[in] film Фильм
 */
void film_free_content(film_t *film);

/**
 * @brief Функция чтения из потока ввода FILE структуры film_t
 *
 * @param[in] file поток ввода
 * @param[out] film указатель на структуру
 * @return код ошибки
 */
int film_read(FILE *file, film_t *film);

/**
 * @brief Функция чтения из потока ввода FILE структуры film_t
 *
 * @param[in] file поток ввода
 * @param[out] film указатель на структуру
 * @return код ошибки
 */
int film_read_ex(FILE *file, film_t *film);

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
