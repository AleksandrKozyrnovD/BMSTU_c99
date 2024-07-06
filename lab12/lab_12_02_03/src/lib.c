#include <stdlib.h>
#include <stdbool.h>
#include "lib.h"

int generate_prime_numbers(long long *array, size_t n)
{
    if (!n)
        return 1;
    if (!array)
    {
        return 1;
    }
    
    bool is_prime;
    size_t curr_size = 0;
    array[0] = 2;
    curr_size++;
    long long num = 3;

    for (; curr_size < n; num += 2)
    {
        is_prime = true;
        for (size_t i = 0; i < curr_size && is_prime; i++)
        {
            if (num % array[i] == 0)
                is_prime = false;
        }
        if (is_prime)
            array[curr_size++] = num;
    }

    return 0;
}

int insert_after_even(int *original, size_t n, int *new_array, size_t *k, int num)
{
    size_t curr_size = 0;

    if (!new_array)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (original[i] % 2 == 0)
                curr_size += 2;
            else
                curr_size++;
        }
        *k = curr_size;
        return 1;
    }

    for (size_t i = 0; i < n; i++)
    {
        if (original[i] % 2 == 0)
        {
            new_array[curr_size++] = original[i];
            new_array[curr_size++] = num;
        }
        else
            new_array[curr_size++] = original[i];
    }

    return 0;
}

