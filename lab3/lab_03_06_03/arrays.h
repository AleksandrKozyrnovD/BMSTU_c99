#ifndef H_ARRAY
#define H_ARRAY

#include <stdio.h>
#include <stddef.h>
#include "errorcode.h"

#define MAX_ARRAY_SIZE 10


/*Функция для спирального заполнения матрицы против часовой стрелки
Принимает матрицу, количество строк, количество столбцов
Ничего не возвращает*/
void fill_spiral_matrix(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns);

#endif
