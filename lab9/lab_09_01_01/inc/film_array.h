#ifndef FILM_ARRAY_H__
#define FILM_ARRAY_H__

#include <stdio.h>
#include <stddef.h>
#include "film.h"
#include "error.h"

#define TITLE_CHOICE 0
#define NAME_CHOICE 1
#define YEAR_CHOICE 2

/**
 * @brief Функция подсчета количества фильмов в файле
 *
 * @param[in] file Файл
 * @param[out] count Количество
 * @return Код ошибки
 */
int film_count(FILE *file, size_t *count);

/**
 * @brief Функция считывания фильмов из файла в созданный массив 
 *
 * @param[in] file Файл
 * @param[in,out] films Массив фильмов
 * @param[in] n Их количество
 * @param[in] cmp Сравнитель
 * @return 
 */
int film_array_read(FILE *file, film_t *films, size_t n, comparator_t cmp);

/**
 * @brief Функция создания массива фильмов из файла
 *
 * @param[in] file Файл
 * @param[out] films Массив фильмов
 * @param[out] n Их количество
 * @param[in] cmp Сравнитель
 * @return 
 */
int film_array_create(FILE *file, film_t **films, size_t *n, comparator_t cmp);

/**
 * @brief Функция освобождения содержимого в массиве фильмов
 *
 * @param[in,out] films Массив фильмов
 * @param[in] n Его размер
 */
void film_array_free(film_t *films, size_t n);

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
 * @param[out] dst Указатель на структуру с результатом
 * @param[in] what По какой структуре ищем
 * @param[in] cmp Сравнитель для структур
 * @return Код ошибки
 */
int film_array_search(const film_t *films, size_t size, film_t *dst, const film_t *what, comparator_t cmp);

#endif

