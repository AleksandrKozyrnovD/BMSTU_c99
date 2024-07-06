#ifndef __SORTED_ARRAY_H__
#define __SORTED_ARRAY_H__

#include <stddef.h>

typedef enum
{
    OK, FOUND, NOT_FOUND, ERR_MEM
} pair_return;

typedef struct pair_t
{
    /*
     * Пара ключ-значение
     * */
    char *key;
    int value;
} pair_t;

int binary_search(pair_t *array, size_t size, const char *key, size_t *index);

int pair_create(pair_t *ptr, const char *key, int val);

void clear_element(pair_t *array, size_t index);

int insert(pair_t *array, size_t size, const char *key, int val);

#endif

