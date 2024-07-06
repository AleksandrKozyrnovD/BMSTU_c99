#include "../inc/comparator.h"
// #include <stdio.h>

int compare_int(const void *left, const void *right)
{
    const int *l = left;
    const int *r = right;
    
    // printf("%d :: %d\n", *l, *r);
    // printf("%p :: %p\n", l, r);

    return *l - *r;
}

