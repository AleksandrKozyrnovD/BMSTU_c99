#include <stdio.h>
#include "associative_array.h"


int main(void)
{
    assoc_array_t array = assoc_array_create();
    char buf[256];

    for (size_t i = 0; i < 10000; i++)
    {
        snprintf(buf, 256, "%zu", i);
        if (assoc_array_insert(array, buf, i) != ASSOC_ARRAY_OK)
            printf("Failt insert at %s\n", buf);
    }
    
    int *num = NULL;
    for (size_t i = 0; i < 10000; i++)
    {
        snprintf(buf, 256, "%zu", i);
        if (assoc_array_find(array, buf, &num) != ASSOC_ARRAY_OK)
            printf("Failt find at %s\n", buf);
    }

    for (size_t i = 0; i < 10000; i++)
    {
        snprintf(buf, 256, "%zu", i);
        if (assoc_array_remove(array, buf) != ASSOC_ARRAY_OK)
            printf("Failt insert at %s\n", buf);
    }
    
    assoc_array_destroy(&array);
    return 0;
}
