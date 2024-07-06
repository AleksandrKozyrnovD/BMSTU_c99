#ifndef __ADDITIONALS_H__
#define __ADDITIONALS_H__

#include <stdio.h>
#include "structures.h"
#include "errorcode.h"

/**
 * @brief Функция для превращения бинарного файла в текстовый
 * 
 * @param[in] file_source Бинарный файл
 * @param[in] file_dst Текстовый файл
 * 
 * @returns
 * Код ошибки
*/
int b2t(FILE *file_source, FILE *file_dst);

/**
 * @brief Функция для превращения текстового файла в бинарный
 * 
 * @param[in] file_source Текстовый файл
 * @param[in] file_dst Бинарный файл
 * 
 * @returns
 * Код ошибки
*/
int t2b(FILE *file_source, FILE *file_dst);


#endif
