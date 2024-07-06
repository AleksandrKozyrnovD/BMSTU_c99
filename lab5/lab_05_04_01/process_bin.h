#ifndef __PROCESS_BIN_H__
#define __PROCESS_BIN_H__

#include <stdio.h>
#include "structures.h"
#include "errorcode.h"

/**
 * @brief Функция для сортировки студентов по фамилии (имени, если фамилии одинаковы)
 * 
 * @param[in] file Указатель на файл
 * 
 * @returns
 * Код ошибки
*/
int sort_students_in_file(FILE *file);

/**
 * @brief Вспомогательная функция для запись студента в файл. По заданию не требуется
*/
int write_student_bin(FILE *file, long pos, student_t *student);


/**
 * @brief Вспомогательная функция для печати содержимого всего бинарного файла. По заданию не требуется
*/
int print_bin(FILE *file_source, FILE *file_dst);

#endif
