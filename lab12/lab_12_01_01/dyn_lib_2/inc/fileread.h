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
 * @return Кол-во чисел
 */
size_t count_int(FILE *file);

/**
 * @brief Функция для заполнения массива числами из файла
 *
 * @param[in] file Файловый указатель
 * @param[in] pbeg Указатель на начало массива
 * @param[in] pend Указатель на следующий после последнего элемента элемент массива
 * @return Код ошибки
 */
int fill_array(FILE *file, int *pbeg, int *pend);

#endif

