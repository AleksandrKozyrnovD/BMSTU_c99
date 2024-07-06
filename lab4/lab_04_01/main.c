#include <string.h>
#include "my_string.h"
#include "includes.h"

#define MAX_WORD_SIZE 16
#define NUMBER_OF_TESTS 4



int main(void)
{
    char array1[NUMBER_OF_TESTS][MAX_WORD_SIZE] = { "0123456789", "testo", "hlopec", "" };
    char array2[NUMBER_OF_TESTS][MAX_WORD_SIZE] = { "9876", "ostet", "hlop", "" };
    char chars[NUMBER_OF_TESTS] = { '\0', 't', 'o', 'h' };

    size_t count_errors = 0;

    for (size_t i = 0; i < NUMBER_OF_TESTS; i++)
    {
        if (my_strpbkr(array1[i], array2[i]) != strpbrk(array1[i], array2[i]))
            count_errors++;
        if (my_strspn(array1[i], array2[i]) != strspn(array1[i], array2[i]))
            count_errors++;
        if (my_strcspn(array1[i], array2[2]) != strcspn(array1[i], array2[2]))
            count_errors++;
        if (my_strchr(array1[i], chars[i]) != strchr(array1[i], chars[i]))
            count_errors++;
        if (my_strrchr(array1[i], chars[i]) != strrchr(array1[i], chars[i]))
            count_errors++;
    }

    printf("Errors == %zu\n", count_errors);

    return count_errors;
}
