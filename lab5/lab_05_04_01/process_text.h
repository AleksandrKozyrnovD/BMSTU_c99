#ifndef __PROCESS_TEXT_H__
#define __PROCESS_TEXT_H__

#include <stdio.h>
#include "structures.h"
#include "errorcode.h"

/**
 * @brief Печатает строки в файл, если фамилия содержит заданную строку в начале
 *
 * @param file_source Указатель на файл-источник
 * @param file_dest Указатель на файл-приемник
 * @param prefix Строка, на которую должны начинаться строки фамилии
 * 
 * @returns
 * Код ошибки
 */
int print_if_prefix(FILE *file_source, FILE *file_dest, char *prefix);

#endif
