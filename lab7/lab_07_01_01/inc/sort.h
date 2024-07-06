#ifndef SORT_H__
#define SORT_H__

#include <stddef.h>

//Тип сравнителя
typedef int (*comparator_t)(const void *, const void *);

/**
 * @brief Сортировка вставками и двоичным поиском
 *
 * @param[in,out] base Указатель на начало массива
 * @param[in] nmemb Количество элементов массива
 * @param[in] size Размер элемента массива
 * @param[in] cmp Указатель на функцию сравнителя
 */
void mysort(void *base, size_t nmemb, size_t size, comparator_t cmp);

#endif

