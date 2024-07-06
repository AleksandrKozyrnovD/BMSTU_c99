#ifndef H_ARRAY
#define H_ARRAY

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errorcode.h"

#define MAX_ARRAY_SIZE 10


/*Функция, проверяющая наличие цифры в числе
Принимает число и цифру
Возвращает правду или ложь*/
bool have_digit(int number, int digit);

/*Функция для нахождения цифры в столбце матрицы
Принимает матрицу, количество строчек и индекс столбца и число, которое будем искать
Возвращает правду или ложь*/
bool is_column_has_digit(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t column_index, int digit);

/*Функция для удаления элемента по индексу в массиве
Принимает массив, его размер, индекс
Ничего не возвращает*/
void delete(int *array, size_t size, size_t index);

/*Функция для удаления столбца в матрике
Принимает матрицу, количество строчек, указатель на количество столбцов и индекс удаляемой колонки
Ничего не возвращает*/
void delete_column(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t *columns, size_t index);


/*Функция для нахождения столбцов, которые следует удалить
Принимает матрицу, строки, столбцы это матрицы, массив, содержащий индексы удаляемых столбцов и его размер, а также число, с помощью которого ищется какой столбец будет удален
Возвращает код ошибки*/
int find_all_columns(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t columns, size_t *columns_delete, size_t *amount, size_t digit);


/*Функция для удаления всех столбцов матрицы с найденным числом
Принимает матрицу, количество строчек, указатель на количество столбцов и число
Возвращает код ошибки*/
int delete_all_columns(int matrix[][MAX_ARRAY_SIZE], size_t rows, size_t *columns, size_t digit);


#endif
