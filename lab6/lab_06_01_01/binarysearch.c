#include <string.h>
#include <assert.h>
#include "binarysearch.h"


// int binary_search_year(const film_t *films, size_t size, int what)
// {
//     //assert size != 0
//     assert((size > 0));
//     int left = 0, right = size - 1, mid;
//     while (left <= right)
//     {
//         mid = (right + left) / 2;
//         if (films[mid].year < what)
//             left = mid + 1;
//         else if (films[mid].year > what)
//             right = mid - 1;
//         else
//             return mid;
//     }
//
//     return -1;
// }
//
// int binary_search_title(const film_t *films, size_t size, const char *what)
// {
//     //assert size != 0
//     assert((size > 0));
//     int left = 0, right = size - 1, mid;
//     int compare_score = 0;
//     while (left <= right)
//     {
//         mid = (right + left) / 2;
//         compare_score = strcmp(what, films[mid].title);
//
//         if (compare_score > 0)
//             left = mid + 1;
//         else if (compare_score < 0)
//             right = mid - 1;
//         else
//             return mid;
//     }
//
//     return -1;
// }
//
// int binary_search_name(const film_t *films, size_t size, const char *what)
// {
//     //assert size != 0
//     assert((size > 0));
//     int left = 0, right = size - 1, mid;
//     int compare_score = 0;
//     while (left <= right)
//     {
//         mid = (right + left) / 2;
//         // compare_score = film_cmp_name(what, films + mid);
//         compare_score = strcmp(what, films[mid].name);
//
//         if (compare_score > 0)
//             left = mid + 1;
//         else if (compare_score < 0)
//             right = mid - 1;
//         else
//             return mid;
//     }
//
//     return -1;
// }

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

// int binary_search_year_index(const film_t *films, size_t size, const film_t *what)
// {
//     //assert size != 0
//     assert((size > 0));
//     int left = 0, right = size - 1, mid;
//     int compare_score = 0;
//     while (left <= right)
//     {
//         mid = (right + left) / 2;
//         // printf("Index in BS: %d\nLeft: %d\nRight: %d\n", mid, left, right);
//         // printf("what: %s and film: %s\n", what->title, films[mid].title);
//         compare_score = film_cmp_year(what, films + mid);
//
//         if (compare_score > 0)
//             left = mid + 1;
//         else if (compare_score < 0)
//             right = mid - 1;
//         else
//             return mid;
//     }
//
//     return left;
// }
//
// int binary_search_title_index(const film_t *films, size_t size, const film_t *what)
// {
//     //assert size != 0
//     assert((size > 0));
//     int left = 0, right = size - 1, mid;
//     int compare_score = 0;
//     while (left <= right)
//     {
//         mid = (right + left) / 2;
//         // printf("Index in BS: %d\nLeft: %d\nRight: %d\n", mid, left, right);
//         // printf("what: %s and film: %s\n", what->title, films[mid].title);
//         compare_score = film_cmp_title(what, films + mid);
//
//         if (compare_score > 0)
//             left = mid + 1;
//         else if (compare_score < 0)
//             right = mid - 1;
//         else
//             return mid;
//     }
//
//     return left;
// }
//
// int binary_search_name_index(const film_t *films, size_t size, const film_t *what)
// {
//     //assert size != 0
//     assert((size > 0));
//     int left = 0, right = size - 1, mid;
//     int compare_score = 0;
//     while (left <= right)
//     {
//         mid = (right + left) / 2;
//         compare_score = film_cmp_name(what, films + mid);
//
//         if (compare_score > 0)
//             left = mid + 1;
//         else if (compare_score < 0)
//             right = mid - 1;
//         else
//             return mid;
//     }
//
//     return left;
// }
//
