#ifndef H_ARRAY
#define H_ARRAY

#include <stdio.h>
#include <stddef.h>
#include "errorcode.h"

#define MAX_ARRAY_SIZE 10


/*Функция, меняющая местами значения двух массивов
Принимает массивы и их размер
Ничего не возвращает*/
void swap_strings(int *string_one, int *string_second, size_t columns);

/*Функция, ищущая минимальный элемент в строчке
Принимает массив и его размер
Возвращает минимум*/
int get_min(const int *array, size_t size);

/*Функция для сортировки матрицы по строкам
Принимает матрицы, количество строк и столбцов
Ничего не возвращает*/
void sort(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns);

#endif
