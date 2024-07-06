#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "errorcode.h"

/**
 * @brief Функция для нахождения среднего значения из файла. Перемещает указатель в конец файла
 * 
 * @param[in] file Файловый указатель
 * @param[out] average Среднее значение
 * 
 * @returns
 * Код ошибки
*/
int get_average(FILE *file, double *average);

/**
 * @brief Функция для нахождения дисперии из файла. Перемещает указатель в конец файла
 * 
 * @param[in] file Файловый указатель
 * @param[in] average Среднее значение из этого файла (желательно)
 * 
 * @returns
 * Дисперсия
*/
double compute_disperse(FILE *file, double average);

#endif
