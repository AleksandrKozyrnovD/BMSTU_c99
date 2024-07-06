#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "node.h"

/**
 * @brief Функция нахождения высоты узла
 *
 * @param[in] root Узел дерева
 * @return Высота узла
 */
static size_t height(const node_t *root)
{
    size_t left_h, right_h;

    if (!root)
        return 0;

    if (!root->left)
        left_h = 0;
    else
        left_h = 1 + root->left->height;

    if (!root->right)
        right_h = 0;
    else
        right_h = 1 + root->right->height;

    if (left_h > right_h)
        return left_h;
    return right_h;
}

/**
 * @brief Функция поворота трех узлов АВЛ-дерева влево
 *
 * @param[in] root Узел текущий
 * @return Новый узел
 */
static node_t *rotate_left(node_t *root)
{
    node_t *right = root->right;
    if (!right)
        return root;
    root->right = right->left;
    right->left = root;

    root->height = height(root);
    right->height = height(right);
    
    return right;
}

/**
 * @brief Функция поворота трех узлов АВЛ-дерева вправо
 *
 * @param[in] root Узел текущий
 * @return Новый узел
 */
static node_t *rotate_right(node_t *root)
{
    node_t *left = root->left;
    if (!left)
        return root;
    root->left = left->right;
    left->right = root;

    root->height = height(root);
    left->height = height(left);

    return left;
}

/**
 * @brief Балансирующий фактор. Проверяет разницу высот левого и правого поддеревьев
 *
 * @param[in] root Узел дерева
 * @return Фактор
 */
static int balance_factor(node_t *root)
{
    int left_height, right_height;

    if (!root)
        return 0;

    if (!root->left)
        left_height = 0;
    else
        left_height = 1 + root->left->height;

    if (!root->right)
        right_height = 0;
    else
        right_height = 1 + root->right->height;

    return left_height - right_height;
}

node_t *tree_insert(node_t *root, const char *key, int num, assoc_array_error_t *rc)
{
    /* Если дерево пустое, то корень такой */
    if (root == NULL)
    {
        node_t *newnode = node_create(key, num);
        if (!newnode)
        {
            *rc = ASSOC_ARRAY_MEM;
            return NULL;
        }
        root = newnode;
    }
    else
    {
        /* Иначе ищем по дереву нужное место */
        int cmp_score = strcmp(key, root->key);
        if (cmp_score > 0)
        {
            /* Рекурсивно ищем нужный узел */
            root->right = tree_insert(root->right, key, num, rc);
            
            /* Балансируем дерево с помощью простых поворотов */
            if (balance_factor(root) == -2)
            {
                if (strcmp(key, root->right->key) > 0)
                    root = rotate_left(root);
                else
                {
                    root->right = rotate_right(root->right);
                    root = rotate_left(root);
                }
            }
        }
        else
        {
            /* Рекурсивно ищем нужный узел */
            root->left = tree_insert(root->left, key, num, rc);

            /* Балансируем дерево с помощью простых поворотов */
            if (balance_factor(root) == 2)
            {
                if (strcmp(key, root->left->key) < 0)
                    root = rotate_right(root);
                else
                {
                    root->left = rotate_left(root->left);
                    root = rotate_right(root);
                }
            }
        }
    }
    
    /* Новая высота узла */
    root->height = height(root);

    return root;
}

node_t *tree_delete(node_t *root, const char *key)
{
    // char *keytmp = NULL;
    node_t *temp = NULL;
    
    /* Если дерево пустое */
    if (!root)
        return NULL;

    int cmp_score = strcmp(key, root->key);
    
    /* Ищем наш узел */
    if (cmp_score > 0)
    {
        root->right = tree_delete(root->right, key);

        if (balance_factor(root) == 2)
        {
            if (balance_factor(root->left) >= 0)
                root = rotate_right(root);
            else
            {
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }
    else if (cmp_score < 0)
    {
        root->left = tree_delete(root->left, key);

        if (balance_factor(root) == -2)
        {
            if (balance_factor(root->right) >= 0)
                root = rotate_left(root);
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else
    {
        if (root->right)
        {
            /* temp - самый левый потомок правого поддерева */
            temp = root->right;
            while (temp->left)
                temp = temp->left;
            
            /* Заменяем ключ с потомка */
            // keytmp = root->key;
            free(root->key);
            root->num = temp->num;
            root->key = strdup(temp->key);
            
            /* Удалим этого потомка (по факту у нас к этому моменту два одинаковых узла, поэтому удаляем копию)*/
            root->right = tree_delete(root->right, temp->key);

            if (balance_factor(root) == 2)
            {
                if (balance_factor(root->left) >= 0)
                    root = rotate_right(root);
                else
                {
                    root->left = rotate_left(root->left);
                    root = rotate_right(root);
                }
            }
        }
        else
        {
            /* Очищаем память под весь узел. Но возвращаем левый.
             *
             * Этот алгоритм предусматривает как узел с одним наследником, так и узел-лист.
             *
             * Этот else возникает, заметим, только в случае, когда правого поддерева нет,
             * то есть узел гарантировано с одним наследником или без.
             *
             * Если наследник есть, он возвращается, иначе NULL (по определению моего узла он либо NULL, либо указатель на узел).
             * */
            node_t *temp = root->left;
            free(root->key);
            free(root);
            return temp;
            // free(root->key);
        }
    }
    
    // free(keytmp);
    root->height = height(root);
    
    return root;
}

node_t *tree_search(node_t *root, const char *key)
{
    if (!root)
        return NULL;

    int cmp_score = strcmp(root->key, key);
    
    if (cmp_score == 0)
        return root;
    else if (cmp_score > 0)
        return tree_search(root->left, key);
    else
        return tree_search(root->right, key);
}

void inorder(node_t *root, void (*action)(const char *, int *, void *), void *param)
{
    if (!root)
        return;

    inorder(root->left, action, param);
    action(root->key, &root->num, param);
    inorder(root->right, action, param);
}

void preorder(node_t *root, void (*action)(const char *, int *, void *), void *param)
{
    if (!root)
        return;

    action(root->key, &root->num, param);
    preorder(root->left, action, param);
    preorder(root->right, action, param);
}

void postorder(node_t *root, void (*action)(const char *, int *, void *), void *param)
{
    if (!root)
        return;

    postorder(root->left, action, param);
    postorder(root->right, action, param);
    action(root->key, &root->num, param);
}

