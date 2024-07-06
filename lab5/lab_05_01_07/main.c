#include <stdio.h>
#include "process.h"
#include "errorcode.h"

#define MAX_ARRAY_SIZE 10


int main(void)
{
    FILE *file = stdin;
    size_t count = 0;

    if (process(file, &count) != EXIT_SUCCESS)
    {
        return ERR_IO;
    }

    printf("%zu\n", count);

    return EXIT_SUCCESS;
}
