#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "errors.h"
#include "node.h"

node_t *node_create(void)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    tmp->next = NULL;
    tmp->str[0] = 0;

    return tmp;
}

void node_free(node_t *node)
{
    if (!node)
        return;
    node->next = NULL;
    free(node);
}

void node_print(FILE *file, const node_t *node)
{
    for (size_t i = 0; i < N && node->str[i]; i++)
        fprintf(file, "%c", node->str[i]);
}

errors_t node_read(char *str, node_t **node, size_t *start)
{
    if (!str)
        return ERR_IO;

    if (*node == NULL)
        *node = node_create();

    if (!*node)
        return ERR_MEM;

    char c = 0;
    size_t i = 0;
    for (; i < N && (c = str[(*start)++]) != '\n' && c != 0; i++)
        (*node)->str[i] = c;

    if (i == 0 && c == 0)
    {
        node_free(*node);
        *node = NULL;
        return ERR_IO;
    }
    if (i == N)
        return FULL;
    return NOT_FULL;
}

errors_t node_read_ex(char *str, node_t **node, size_t *start, char *lastchar)
{
    if (*node == NULL)
        *node = node_create();

    if (!*node)
        return ERR_MEM;
    
    
    char c = 0;
    size_t i = 0;
    size_t spaces = 0;
    for (; i < (N + spaces) && (c = str[(*start)++]) != '\n' && c != 0; i++)
    {
        if (isspace(*lastchar) && isspace(c))
        {
            spaces++;
            continue;
        }
        *lastchar = c;
        (*node)->str[i - spaces] = c;
    }
    if (i == 0 && c == 0)
    {
        node_free(*node);
        *node = NULL;
        return ERR_IO;
    }

    if (i == N + spaces)
        return FULL;
    return NOT_FULL;
}
