#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include "errors.h"
#include <stddef.h>

#define N 4

typedef struct node_t node_t;

struct node_t
{
    char str[N];

    node_t *next;
};

/**
 * @brief Создание узла. Динамически выделяет память на его структуру, но не выделяет память под информационную часть
 *
 * @return Указатель на узел
 */
node_t *node_create(void);

/**
 * @brief Освобобождение памяти из-поз узла
 *
 * @param[in] node Указатель на узел
 */
void node_free(node_t *node);

/**
 * @brief Функция печати узла (в данном случае часть строки)
 *
 * @param[in] file Указатель на файл
 * @param[in] node Указатель на узел
 */
void node_print(FILE *file, const node_t *node);

#endif

