#ifndef BINARYSEARCH_H__
#define BINARYSEARCH_H__

#include "film.h"
#include "film_array.h"

/**
 * @brief Функции для поиска по полю бинарным способом
 *
 * @param[in] films Массив структур фильмов
 * @param[in] size Размер массива структур фильмов
 * @param[in] year Какой год искать
 * @return Номер позиции
 */
// int binary_search_year(const film_t *films, size_t size, int year);

/**
 * @brief Функции для поиска по полю бинарным способом
 *
 * @param[in] films Массив структур фильмов
 * @param[in] size Размер массива структур фильмов
 * @param[in] what Какое название фильма искать
 * @return Номер позиции
 */
// int binary_search_title(const film_t *films, size_t size, const char *what);

/**
 * @brief Функции для поиска по полю бинарным способом
 *
 * @param[in] films Массив структур фильмов
 * @param[in] size Размер массива структур фильмов
 * @param[in] what Какое имя у создателя
 * @return Номер позиции
 */
// int binary_search_name(const film_t *films, size_t size, const char *what);

/**
 * @brief Функции для поиска по полю бинарным способом
 *
 * @param[in] films Массив структур фильмов
 * @param[in] size Размер массива структур фильмов
 * @param[in] film Структура, с которой сравниваем
 * @param[in] cmp Сравнитель для структуры
 * @return Номер позиции
 */
int binary_search(const film_t *films, size_t size, const film_t *film, comparator_t cmp);

#endif

