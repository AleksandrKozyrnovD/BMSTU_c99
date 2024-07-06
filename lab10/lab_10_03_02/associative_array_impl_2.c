#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "associative_array.h"
#include "tree.h"

/*
 * АВЛ-дерево.
 *
 * По определнию вставка в такое дерево приведет к сбалансированному дереву (разница высоты двух поддеревьев не больше 1)
 *
 * Вставка: O(log(n))
 * Удаление: O(log(n))
 * Нахождение: O(log(n))
 * min: O(log(n))
 * max: O(log(n))
 *
 * Память: sizeof(node_t) * n байт
 *         32 * n байт
 *
 * */


typedef struct assoc_array_type
{
    /*
     * Указатель на корень АВЛ-дерева
     * */
    node_t *root;
} assoc_array_type;


assoc_array_t assoc_array_create(void)
{
    assoc_array_t array = NULL;
    
    array = malloc(sizeof(assoc_array_type));
    if (!array)
        return NULL;
    
    array->root = NULL;
    // array->size = 0;
    return array;
}

static void myfree(node_t *root)
{
    if (!root)
        return;
    
    /*
     * Очистка по postorder
     *
     * Поленился вклеить сюда АВЛ-льный postorder, записанный в tree.h
     * */
    myfree(root->left);
    myfree(root->right);
    node_free(&root);
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!(*arr) || !arr)
        return;
    
    myfree((*arr)->root);
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;
    int *temp = NULL;
    
    if (assoc_array_find(arr, key, &temp) == ASSOC_ARRAY_OK)
        return ASSOC_ARRAY_KEY_EXISTS;
    
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    node_t *tmp = tree_insert(arr->root, key, num, &rc);
    if (rc != ASSOC_ARRAY_OK)
        return rc;
    if (!tmp)
        return ASSOC_ARRAY_MEM;

    arr->root = tmp;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || !num || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *tmp = tree_search(arr->root, key);
    if (!tmp)
    {
        *num = NULL;
        return ASSOC_ARRAY_NOT_FOUND;
    }
    else
    {
        *num = &tmp->num;
        return ASSOC_ARRAY_OK;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    int *temp = NULL;
    if (assoc_array_find(arr, key, &temp) == ASSOC_ARRAY_OK)
    {
        arr->root = tree_delete(arr->root, key);
        return ASSOC_ARRAY_OK;
    }
    else
        return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    myfree(arr->root);
    arr->root = NULL;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *, int *, void *), void *param)
{
    if (!arr || !action || !param)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    /*
     * inorder здесь потому, что обход произойдет от наименьшего ключа к наибольшему
     *
     * Чисто в теории сделано это так, чтобы был паритет с таблицей пара-ключ.
     * Или потому, что применение функции должно производиться отнаименьшего к большему
     * */

    if (arr->root)
        inorder(arr->root, action, param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    if (!arr->root)
    {
        *num = NULL;
        return ASSOC_ARRAY_NOT_FOUND;
    }
    
    node_t *tmp = arr->root;
    while (tmp->left)
        tmp = tmp->left;
    *num = &tmp->num;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    if (!arr->root)
    {
        *num = NULL;
        return ASSOC_ARRAY_NOT_FOUND;
    }

    node_t *tmp = arr->root;
    while (tmp->right)
        tmp = tmp->right;
    *num = &tmp->num;

    return ASSOC_ARRAY_OK;
}

