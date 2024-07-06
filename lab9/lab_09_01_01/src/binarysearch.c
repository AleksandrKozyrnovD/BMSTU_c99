#include <string.h>
#include <assert.h>
#include "binarysearch.h"


int binary_search(const film_t *films, size_t size, const film_t *film, comparator_t cmp)
{
    //assert size != 0
    assert((size > 0));
    int left = 0, right = size - 1, mid;
    int compare_score = 0;
    while (left <= right)
    {
        mid = (right + left) / 2;
        // compare_score = film_cmp_name(what, films + mid);
        compare_score = cmp(film, films + mid);

        if (compare_score > 0)
            left = mid + 1;
        else if (compare_score < 0)
            right = mid - 1;
        else
            return mid;
    }

    return -1;
}

