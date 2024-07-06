#ifndef H_ARRAY
#define H_ARRAY

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "errorcode.h"

#define MAX_ARRAY_SIZE 10

typedef int matrix[][MAX_ARRAY_SIZE]; //по советам Яковенко.


/*Функция для проверки строчки на то, что она содержит монотонную последовательность
Принимает указатель на массив и его размер
Возвращает правду или ложь*/
bool is_sequence(const int *array, size_t size);

/*Функция, которая ищет все строчки, содержащие монот. последовательности и записывает результат в другой массив
Принимает матрицу, количество строк и столбцов этой матрицы, указатель на массив
Ничего не возвращает*/
void find_sequence(matrix matrix, size_t rows, size_t columns, int *array);

#endif
