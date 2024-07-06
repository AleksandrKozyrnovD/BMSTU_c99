#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdio.h>
#include "errorcode.h"

/**
 * @brief Функция для создания/перезаписывания бинарного файла, заполненного count-раз числами
 * 
 * @param[in] file Файловый указатель
 * @param[in] count Сколько чисел будет в файле.
 * 
 * @returns
 * Код ошибки
*/
int create_file(FILE *file, size_t count);

/**
 * @brief Функция для печати содержимого бинарного файла в выходной файл
 * 
 * @param[in] file Файловый указатель
 * @param[in] dst Указатель на выходной файл
 * 
 * @returns
 * Код ошибки
*/
int print_file(FILE *file, FILE* dst);

/**
 * @brief Функция для сортировки содержимого бинарного файла
 * 
 * @param[in] file Файловый указатель
 * 
 * @returns
 * Код ошибки
*/
int sort_file(FILE *file);

#endif
