#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include "node.h"


node_t *node_create(const char *key, int num)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;

    node->key = strdup(key);
    if (!node->key)
    {
        free(node);
        return NULL;
    }
    node->num = num;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;

    return node;
}

void node_free(node_t **node)
{
    free((*node)->key);
    free(*node);
    *node = NULL;
}

