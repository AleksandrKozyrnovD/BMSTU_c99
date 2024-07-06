#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "sorted_array.h"


int binary_search(pair_t *array, size_t size, const char *key, size_t *index)
{
    if (!size)
        return 0;

    size_t left = 0;
    size_t right = size - 1;

    size_t mid = 0;
    int score = 0;

    while (left < right)
    {
        // printf("Left: %zu, mid: %zu, right = %zu\n", left, mid, right);
        mid = left + (right - left) / 2;
        score = strcmp(key, array[mid].key);

        if (score == 0)
        {
            *index = mid;
            // printf("Index = %zu\n", mid);
            return FOUND;
        }
        else if (score < 0)
        {
            right = mid;
        }
        else
            left = mid + 1;
    }
    
    if (!strcmp(key, array[right].key))
    {
        *index = right;
        return FOUND;
    }
    *index = size + 1;

    return NOT_FOUND;
}

int pair_create(pair_t *ptr, const char *key, int val)
{
    ptr->key = strdup(key);
    if (!ptr->key)
        return ERR_MEM;
    
    ptr->value = val;
    return OK;
}

void clear_element(pair_t *array, size_t index)
{
    free(array[index].key);
}

int insert(pair_t *array, size_t size, const char *key, int val)
{
    size_t i = size;

    for (; i != 0 && strcmp(array[i - 1].key, key) > 0; --i)
    {
        array[i] = array[i - 1];
    }
    if (pair_create(array + i, key, val) != OK)
        return ERR_MEM;
    return OK;
}
