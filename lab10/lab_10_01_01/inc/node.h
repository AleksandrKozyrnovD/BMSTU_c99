#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

typedef struct node node_t;

struct node
{
    void *data;

    node_t *next;
};

/**
 * @brief Создание узла. Динамически выделяет память на его структуру, но не выделяет память под информационную часть
 *
 * @param[in] data Указатель на информационную часть
 * @return Указатель на узел
 */
node_t *node_create(void *data);

/**
 * @brief Освобобождение памяти из-поз узла
 *
 * @param[in] node Указатель на узел
 */
void node_free(node_t *node);

/**
 * @brief Функция печати узла (в данном случае студентов)
 *
 * @param[in] file Указатель на файл
 * @param[in] node Указатель на узел
 */
void node_print(FILE *file, const node_t *node);

/**
 * @brief Функция сравнения узлов (???)
 *
 * @param[in] left Указатель на левый
 * @param[in] right Указатель на правый
 * @return Разница целочисленная
 */
int node_cmp(const void *left, const void *right);

#endif

