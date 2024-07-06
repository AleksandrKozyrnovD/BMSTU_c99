#ifndef H_IO
#define H_IO

#include "arrays.h"


/*Функция для ввода целочисленных чисел в матрицу
Принимает указатель на матрицу, количество строк, количество колонок
Возвращает код ошибки*/
int input_matrix(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns);

/*Функция для ввода количества строк и столбцов
Принимает указатели на строчки и колонки
Возвращает код ошибки*/
int validate_input_size(size_t *rows, size_t *columns);

/*Функция для печати массива
Принимает указатель на массив и его размер
Ничего не возвращает*/
void print_array(const int *array, size_t size);

#endif
