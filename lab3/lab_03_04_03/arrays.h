#ifndef H_ARRAY
#define H_ARRAY

#include <stdio.h>
#include <stddef.h>
#include "errorcode.h"

#define MAX_ARRAY_SIZE 10

/*Функция для переформирования квадратной матрицы как на картинке (как это более лаконично сказать?)
Принимает целочисленную матрицу и ее размер
Ничего не возвращает*/
void reshape_matrix(int matrix[][MAX_ARRAY_SIZE], size_t size);

#endif
