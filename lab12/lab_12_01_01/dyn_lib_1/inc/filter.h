#ifndef FILTER_H__
#define FILTER_H__

#include "err.h"

/**
 * @brief Функция-фильтр по заданию
 *
 * @details память на pb_dst выделяется вызывающей стороной
 *
 * @param pb_src Начало исходного массива
 * @param pe_src Конец исходного массива
 * @param pb_dst Начала отфильтрованного массива
 * @return Код ошибки
 */
int key(const int *pb_src, const int *pe_src, int *pb_dst);

/**
 * @brief Функция получения размера отфильтрованного массива
 *
 * @param max Указатель на Максимальный элемент
 * @param min Указатель на Минимальный элемент
 * @return 
 */
int get_filtered_size(const int *max, const int *min);

/**
 * @brief Функция получения наименьшего элемента из массива
 *
 * @param pb Начало массива
 * @param pe Конец массива
 * @return Указатель на наименьший элемент
 */
const int *get_min(const int *pb, const int *pe);

/**
 * @brief Функция получения наибольшего элемента из массива
 *
 * @param pb Начало массива
 * @param pe Конец массива
 * @return Указатель на наибольший элемент
 */
const int *get_max(const int *pb, const int *pe);

#endif

