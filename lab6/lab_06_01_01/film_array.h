#ifndef FILM_ARRAY_H__
#define FILM_ARRAY_H__

#include <stdio.h>
#include <stddef.h>
#include "film.h"
#include "error.h"

#define MAX_N 15
#define TITLE_CHOICE 0
#define NAME_CHOICE 1
#define YEAR_CHOICE 2

/**
 * @brief Функция чтения структур в массив структур типа film_t
 *
 * @param[in] file Поток ввода
 * @param[out] films Массив структур film_t
 * @param[out] size Размер массива структур
 * @param[in] n_max Максимальное количество элементов
 * @param[in] cmp Сравнитель для записей
 * @return Код ошибки
 */
int film_array_read(FILE *file, film_t *films, size_t *size, size_t n_max, comparator_t cmp);

/**
 * @brief Функция вывода массива структур film_t
 *
 * @param[in] file Поток вывода
 * @param[in] films Массив структур film_t
 * @param[in] size Размер массива структур
 */
void film_array_print(FILE *file, const film_t *films, size_t size);

/**
 * @brief Функция вставки в упорядоченный массив структур film_t
 *
 * @param[in,out] films Массив структур film_t
 * @param[in,out] size Размер массива структур
 * @param[in] what Указатель на структуру, которую вставляем
 * @param[in] cmp Сравнитель для записей
 */
void film_array_insert(film_t *films, size_t *size, const film_t *what, comparator_t cmp);

/**
 * @brief Функция автоопределения выбора по строке имени поля
 *
 * @param[in] name Имя поля (title, name, year)
 * @return Код этого поля
 */
int get_choice_by_name(const char *name);

/**
 * @brief Функция поиска по полю
 *
 * @param[in] films Массив структур film_t
 * @param[in] size Размер массива структур
 * @param[out] film Указатель на структуру
 * @param[in] title Титул фильма
 * @return Код ошибки
 */
// int film_array_search_title(const film_t *films, size_t size, film_t *film, const char *title);

/**
 * @brief Функция поиска по полю
 *
 * @param[in] films Массив структур film_t
 * @param[in] size Размер массива структур
 * @param[out] film Указатель на структуру
 * @param[in] name Имя создателя
 * @return Код ошибки
 */
// int film_array_search_name(const film_t *films, size_t size, film_t *film, const char *name);

/**
 * @brief Функция поиска по полю
 *
 * @param[in] films Массив структур film_t
 * @param[in] size Размер массива структур
 * @param[out] film Указатель на структуру
 * @param[in] year Год издания
 * @return Код ошибки
 */
// int film_array_search_year(const film_t *films, size_t size, film_t *film, size_t year);

/**
 * @brief Функция поиска по полю
 *
 * @param[in] films Массив структур film_t
 * @param[in] size Размер массива структур
 * @param[out] dst Указатель на структуру с результатом
 * @param[in] what По какой структуре ищем
 * @param[in] cmp Сравнитель для структур
 * @return Код ошибки
 */
int film_array_search(const film_t *films, size_t size, film_t *dst, const film_t *what, comparator_t cmp);

#endif

