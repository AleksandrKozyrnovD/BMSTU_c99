#include "sort.h"
#include "fileread.h"
#include <assert.h>
#include <string.h>

/**
 * @brief Функция для смены двух элементов местами
 *
 * @param[in,out] l Указатель на левый элемент
 * @param[in,out] r Указатель на правый элемент
 * @param[in] nmem Размер этих двух элементов
 */
static void swap(void *l, void *r, size_t nmem)
{
    char tmp;
    char *pl = l, *pr = r;
    for (size_t i = 0; i < nmem; i++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
        pl++;
        pr++;
    }
}

/**
 * @brief Функция бинарного поиска
 *
 * @param[in] base Указатель на начало массива 
 * @param[in] data Указатель на элемент массива, который ищем
 * @param[in] nmemb Кол-во элементов массива
 * @param[in] size Размер элемента
 * @param[in] cmp Указатель на функцию сравнителя
 * @return Индекс в массиве
 */
// static size_t binary_search(const void *base, const void *data, size_t nmemb, size_t size, comparator_t cmp)
// {
//     assert((nmemb > 0));
//     int left = 0;
//     int right = nmemb - 1;
//     int mid;
//     void *middle;
//     int cmp_score;
//
//     while (left <= right)
//     {
//         mid = left + ((right - left) / 2);
//         middle = (char *) base + (mid * size);
//         
//         cmp_score = cmp(data, middle);
//
//         if (cmp_score == 0)
//             return mid;
//         else if (cmp_score < 0)
//             right = mid - 1;
//         else
//             left = mid + 1;
//     }
//
//     return left;
// }

/**
 * @brief Функция бинарного поиска элемента в массиве
 *
 * @param[in] base Указатель на начало массива
 * @param[in] end Указатель на законец массива
 * @param[in] data Искомый элемент
 * @param[in] size Размер элементов
 * @param[in] cmp Указатель на функцию сравнитель
 * @return Указатель на область, где он должен лежать
 */
// static void *binary_search(const void *base, const void *end, const void *data, size_t size, comparator_t cmp)
// {
//     const char *left = base;
//     const char *right = end;
//     if (left > right)
//         return (void *) (left);
//
//     const char *mid;
//     int cmp_score;
//
//     mid = (left + ((right - left) / size) / 2 * size);
//
//     cmp_score = cmp(data, mid);
//
//     if (cmp_score == 0)
//         return (void *) mid;
//     else if (cmp_score < 0)
//         return binary_search(base, mid - size, data, size, cmp);
//     else
//         return binary_search(left + size, right, data, size, cmp);
// }
static void *binary_search(const void *base, const void *end, const void *data, size_t size, comparator_t cmp)
{
    const char *left = base;
    const char *right = end;
    if (left > right)
        return (void *) (left);

    const char *mid;
    int cmp_score;
    while (left <= right)
    {
        mid = (left + ((right - left) / size) / 2 * size);

        cmp_score = cmp(data, mid);
        if (cmp_score == 0)
            return (void *) mid;
        else if (cmp_score < 0)
            right = mid - size;
        else if (cmp_score > 0)
        {
            left = mid + size;
        }
    }

    return (void *) (left);
}

/**
 * @brief Функция вставки элемента в массив
 *
 * @param[in,out] base Указательна массив
 * @param[in] nmemb Кол-во элементов
 * @param[in] size Размкр элемента
 * @param[in] pos Позиция вставки
 */
// static void insert(void *base, size_t nmemb, size_t size, size_t pos)
// {
//     char *arr = (char*) base;
//     for (size_t i = nmemb; i >= pos + 1; i--)
//         swap(arr + i * size, arr + (i - 1) * size, size);
// }

static void insert_swap(void *start, void *end, size_t size)
{
    char *index = start;
    char *from = end;
    for (char *pcur = from; pcur > index; pcur -= size)
        swap(pcur, pcur - size, size);
}

// static void insert(void *base, void *end, const void *data, size_t size)
// {
//     char *pos = base;
//     char *pend = end;
//
//     for (char *pcur = pend; pcur > pos; pcur -= size)
//     {
//         memcpy(pcur, pcur - size, size);
//     }
//     memcpy(pos, data, size);
// }

void mysort_swap(void *base, size_t nmemb, size_t size, comparator_t cmp)
{
    if (!size)
        return;

    char *pbeg = base;
    char *pend = pbeg + nmemb * size;
    char *index;
    
    for (char *pcur = pbeg + size; pcur < pend; pcur += size)
    {
        index = binary_search(base, pcur - size, pcur, size, cmp);
        insert_swap(index, pcur, size);
    }
}

void mysort_vla(void *base, size_t nmemb, size_t size, comparator_t cmp)
{
    if (!size)
        return;

    char tmp[size]; //VLA
    char *pbeg = base;
    char *pend = pbeg + nmemb * size;
    char *index;

    for (char *pcur = pbeg + size; pcur < pend; pcur += size)
    {
        memcpy(tmp, pcur, size);
        index = binary_search(base, pcur - size, pcur, size, cmp);
        memmove(index + size, index, pcur - index);
        memcpy(index, tmp, size);
    }
}
