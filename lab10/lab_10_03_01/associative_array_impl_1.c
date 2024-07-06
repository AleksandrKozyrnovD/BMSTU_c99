#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "associative_array.h"
#include "sorted_array.h"

/*
 * Таблица динамического массива ключ-значение.
 *
 * По определению, массив у меня упорядоченный, отчего эффективен бинарный поиск по ключу
 *
 * Вставка: O(log(n)), O(n)
 * Удаление: O(N)
 * Нахождение: O(log(n))
 * min: O(1)
 * max: O(1)
 *
 * Память: sizeof(pair_t) * n байт
 *         16 * n байт
 * */

// typedef struct pair_t
// {
//     /*
//      * Пара ключ-значение
//      * */
//     char *key;
//     int value;
// } pair_t;

typedef struct assoc_array_type
{
    /*
     * size - Текущий заполненный размер массива
     * capacity - Выделенное количество памяти на n элементов.
     * */
    size_t size, capacity;

    /*
     * Указатель на массив пар ключ-значение
     * */
    pair_t *array;
} assoc_array_type;

// static int cmp(const void *l, const void *r)
// {
//     return strcmp(l, r);
// }

/**
 * @brief Функция получения индекса во внутреннем массиве
 *
 * @param[in] array Ассоциативный массив
 * @param[in] key Ключ
 * @param[out] index Индекс
 * @return Код ошибки
 */
// static assoc_array_error_t get_index(assoc_array_t array, const char *key, size_t *index)
// {
//     if (!array->size)
//         return 0;
//
//     size_t left = 0;
//     size_t right = array->size - 1;
//
//     size_t mid = 0;
//     int score = 0;
//
//     while (left < right)
//     {
//         // printf("Left: %zu, mid: %zu, right = %zu\n", left, mid, right);
//         mid = left + (right - left) / 2;
//         score = cmp(key, array->array[mid].key);
//
//         if (score == 0)
//         {
//             *index = mid;
//             // printf("Index = %zu\n", mid);
//             return ASSOC_ARRAY_KEY_EXISTS;
//         }
//         else if (score < 0)
//         {
//             right = mid;
//         }
//         else
//             left = mid + 1;
//     }
//     
//     if (!cmp(key, array->array[right].key))
//     {
//         *index = right;
//         return ASSOC_ARRAY_KEY_EXISTS;
//     }
//     *index = array->size + 1;
//
//     return ASSOC_ARRAY_NOT_FOUND;
// }

/**
 * @brief Функция очистки одного элемента
 *
 * @param[in,out] array Ассоциативный массив
 * @param[in] index Его изначальный индекс
 */
// static void clear_element(assoc_array_t array, size_t index)
// {
//     free(array->array[index].key);
// }

/**
 * @brief Создание структуры ключ-значение
 *
 * @param[out] ptr Указатель на пару ключ-значение
 * @param[in] key Ключ
 * @param[in] val Значение
 * @param[in] keysize Размер ключа
 * @param[in] valsize Размер значения
 * @return Код ошибки
 */
// static assoc_array_error_t pair_create(pair_t *ptr, const char *key, int val)
// {
//     ptr->key = strdup(key);
//     if (!ptr->key)
//         return ASSOC_ARRAY_MEM;
//     
//     ptr->value = val;
//     return ASSOC_ARRAY_OK;
// }

/**
 * @brief Функция уменьшения размера ассоциативного массива
 *
 * @param[in,out] array Ассоциативный массив
 */
static void reduce_size(assoc_array_t array)
{
    if (array->size > 0 && array->capacity / array->size >= 2)
    {
        pair_t *tmp = realloc(array->array, sizeof(pair_t) * (array->size + 1));
        if (!tmp)
            return;
        array->array = tmp;
        array->capacity = array->size + 1;
    }
}

static assoc_array_error_t increase_size(assoc_array_t array, size_t newsize)
{
    if (newsize >= array->capacity)
    {
        pair_t *tmp = NULL;
        tmp = realloc(array->array, newsize * 2 * sizeof(pair_t));
        if (!tmp)
            return ASSOC_ARRAY_MEM;
        array->array = tmp;
        array->capacity = newsize * 2;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_t assoc_array_create(void)
{
    assoc_array_t array = NULL;

    array = malloc(sizeof(assoc_array_type));
    if (!array)
        return NULL;
    array->array = malloc(sizeof(pair_t));
    if (!array->array)
    {
        free(array);
        return NULL;
    }

    array->size = 0;
    array->capacity = 1;

    return array;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!(*arr) || !arr)
        return;

    for (size_t i = 0; i < (*arr)->size; i++)
        clear_element((*arr)->array, i);
        // clear_element(*arr, i);

    free((*arr)->array);
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t array, const char *key, int num)
{
    if (!array || !key || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    size_t i = 0;
    if (binary_search(array->array, array->size, key, &i) == FOUND)
        return ASSOC_ARRAY_KEY_EXISTS;
    // if (get_index(array, key, &i) == ASSOC_ARRAY_KEY_EXISTS)
    //     return ASSOC_ARRAY_KEY_EXISTS;

    size_t newsize = array->size + 1;
    if (increase_size(array, newsize) != ASSOC_ARRAY_OK)
        return ASSOC_ARRAY_MEM;

    if (newsize == 1)
    {
        if (pair_create(array->array, key, num) != ASSOC_ARRAY_OK)
            return ASSOC_ARRAY_MEM;
        array->size++;
        return ASSOC_ARRAY_OK;
    }

    
    if (insert(array->array, array->size, key, num) != OK)
        return ASSOC_ARRAY_MEM;
    // pair_t *array_pair = array->array;
    // i = array->size;
    //
    // for (; i != 0 && cmp(array_pair[i - 1].key, key) > 0; --i)
    // {
    //     array_pair[i] = array_pair[i - 1];
    // }
    // if (pair_create(array->array + i, key, num) != ASSOC_ARRAY_OK)
    //     return ASSOC_ARRAY_MEM;
    array->size++;
    
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t array, const char *key, int **num)
{
    if (!array || !key || !num || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    size_t index = 0;
    // if (get_index(array, key, &index) == ASSOC_ARRAY_KEY_EXISTS)
    if (binary_search(array->array, array->size, key, &index) == FOUND)
    {
        *num = &array->array[index].value;
        return ASSOC_ARRAY_OK;
    }
    else
    {
        *num = NULL;
        return ASSOC_ARRAY_NOT_FOUND;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t array, const char *key)
{
    if (!array || !key || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    size_t index = 0;
    // if (get_index(array, key, &index) == ASSOC_ARRAY_KEY_EXISTS)
    if (binary_search(array->array, array->size, key, &index) == FOUND)
    {
        pair_t *pairs = array->array;
        // clear_element(array, index);
        clear_element(array->array, index);
        for (size_t i = index; i < array->size - 1; i++)
            pairs[i] = pairs[i + 1];
        array->size--;
        reduce_size(array);

        return ASSOC_ARRAY_OK;
    }
    else
        return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
        clear_element(arr->array, i);
        // clear_element(arr, i);
    arr->size = 0;
    reduce_size(arr);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *, int *, void *), void *param)
{
    if (!arr || !action || !param)
        return ASSOC_ARRAY_INVALID_PARAM;

    pair_t *array = arr->array;
    for (size_t i = 0; i < arr->size; i++)
        action(array[i].key, &array[i].value, param);
    
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &arr->array[0].value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &arr->array[arr->size - 1].value;

    return ASSOC_ARRAY_OK;
}

