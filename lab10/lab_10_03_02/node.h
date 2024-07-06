#ifndef __NODE_H__
#define __NODE_H__

#include <stddef.h>

typedef struct node_t node_t;

struct node_t
{
    char *key;
    int num;
    size_t height;

    node_t *left, *right;
};

/**
 * @brief Функция создания узла АВЛ-дерева
 *
 * @[in] param key Ключ
 * @param[in] num Число
 * @return NULL или созданный объект
 */
node_t *node_create(const char *key, int num);

/**
 * @brief Функция очистки узла
 *
 * @param[in,out] node Узел АВЛ-дерева. Он станет равным NULL
 */
void node_free(node_t **node);

#endif

