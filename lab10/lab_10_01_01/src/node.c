#include <stdlib.h>
#include "node.h"

node_t *node_create(void *data)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    tmp->next = NULL;
    tmp->data = data;

    return tmp;
}

void node_free(node_t *node)
{
    if (!node)
        return;
    node->next = NULL;
    node->data = NULL;
    free(node);
}


