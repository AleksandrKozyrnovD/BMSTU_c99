#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "errorcode.h"

/**
 * @brief Функция для нахождения локальный максимумов в файле
 * 
 * @param[in] file Файловый указатель
 * @param[out] count Количество найденных локальных максимумов
 * 
 * @returns
 * Код ошибки
*/
int process(FILE *file, size_t *count);

#endif