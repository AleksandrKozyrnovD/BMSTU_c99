#ifndef FILTER_H__
#define FILTER_H__

#include "err.h"

/**
 * @brief Функция-фильтр для массива целых чисел
 *
 * @details Филььтрует все значения от первого минимального/максимального до первого максимального/минимального
 *
 * @param[in] pb_src Указатель на начало фильтруемого массива
 * @param[in] pe_src Указатель на конец фильтруемого массива
 * @param[out] pb_dst Указатель на указатель начала отфильтрованного массива
 * @param[out] pe_dst Указатель на указатель конца отфильтрованного массва
 * @return Код ошибки
 */
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif

