#include <stdlib.h>
#include <string.h>
#include "filter.h"


/**
 * @brief Функция для поиска минимума в массиве целых чисел
 *
 * @param[in] pb Указатель на начало массива
 * @param[in] pe Указатель на законец массива
 * @return Указатель на минимальный элемент
 */
const int *get_min(const int *pb, const int *pe)
{
    const int *pcur = pb;
    const int *min = pcur;

    while (pcur < pe)
    {
        if (*min > *pcur)
            min = pcur;
        pcur++;
    }

    return min;
}


/**
 * @brief Функция для поиска максимума в массиве целых чисел
 *
 * @param[in] pb Указатель на начало массива
 * @param[in] pe Указатель на законец массива
 * @return Указатель на максимальный элемент
 */
const int *get_max(const int *pb, const int *pe)
{
    const int *pcur = pb;
    const int *max = pcur;

    while (pcur < pe)
    {
        if (*max < *pcur)
            max = pcur;
        pcur++;
    }

    return max;
}

int get_filtered_size(const int *max, const int *min)
{
    if (max - min < 0)
    {
        const int *tmp = min;
        min = max;
        max = tmp;
    }
    
    if (max - min - 1 == 0 || *max == *min)
        return 0;

    return max - min - 1;
}

int key(const int *pb_src, const int *pe_src, int *pb_dst)
{
    if (!pb_src || !pe_src || !pb_dst)
        return ERR_IO;

    if (pb_src > pe_src)
        return ERR_IO;

    const int *start = get_min(pb_src, pe_src);
    const int *end = get_max(pb_src, pe_src);
    //
    // // const int *pcur_src;
    // // int *pcur_dst;
    //
    if (end - start < 0)
    {
        const int *tmp = start;
        start = end;
        end = tmp;
    }
    
    if (end - start - 1 == 0 || *end == *start)
        return EMPTY;

    int size = get_filtered_size(start, end);
    if (!size)
        return EMPTY;

    // *pb_dst = (int *)malloc(size * sizeof(int));
    // if (*pb_dst == NULL)
    //     return EMPTY;
    //
    // *pe_dst = *pb_dst + size;
    
    // pcur_src = start + 1; //???????
    // pcur_dst = *pb_dst;
    // while (pcur_src < end)
    // {
    //     *pcur_dst = *pcur_src;
    //     pcur_dst++;
    //     pcur_src++;
    // }
    
    memcpy(pb_dst, start + 1, size * sizeof(int));

    return EXIT_SUCCESSFUL;
}

