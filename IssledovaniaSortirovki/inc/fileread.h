#ifndef FILEREAD_H__
#define FILEREAD_H__

#include <stdio.h>
#include <stdlib.h>
#include "err.h"

/**
 * @brief Функция печати в файл массива целых
 *
 * @param[in] file Файловый указатель
 * @param[in] pbeg Указатель на начало массива
 * @param[in] pend Указатель на конец массива
 */
void print(FILE *file, const int *pbeg, const int *pend);

/**
 * @brief Функция для счета и проверки кол-ва целых чисел в файле
 *
 * @param[in] file Файловый указатель
 * @param[in] size Кол-во чисел в файле
 * @return Код ошибки
 */
// int count_int(FILE *file, size_t *size);
int count_int(FILE *file);

/**
 * @brief Функция для чтения из файла в массив целых чисел
 *
 * @param[in] file Файловый указатель
 * @param[out] array Указатель на указатель на массив целых чисел
 * @param[out] size Размер этого массива
 * @return Код ошибки
 */
int read_into_array(FILE *file, int **array, size_t *size);

#endif

