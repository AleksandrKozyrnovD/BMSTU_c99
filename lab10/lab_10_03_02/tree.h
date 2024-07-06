#ifndef __TREE_H__
#define __TREE_H__

#include <stdbool.h>
#include "associative_array.h"
#include "node.h"

node_t *tree_insert(node_t *root, const char *key, int num, assoc_array_error_t *rc);

node_t *tree_delete(node_t *root, const char *key);

node_t *tree_search(node_t *root, const char *key);

void inorder(node_t *root, void (*action)(const char *, int *, void *param), void *param);

void preorder(node_t *root, void (*action)(const char *, int *, void *param), void *param);

void postorder(node_t *root, void (*action)(const char *, int *, void *param), void *param);


#endif


