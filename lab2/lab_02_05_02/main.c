#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SUCCESSFUL_EXIT 0
#define INCORECT_INPUT 1
#define INCORRECT_SIZE_INPUT 2
#define ARRAY_MAX_SIZE 10

/*Функция для заполнения массива.
Принимает указатель на начало и длину массива.
Возвращает код ошибки.*/
int array_input(int *pointer_begin, int *pointer_end)
{
    int *pointer_current = pointer_begin;

    while (pointer_current < pointer_end)
    {
        if (scanf("%d", pointer_current) != 1)
        {
            return INCORECT_INPUT;
        }
        pointer_current++;
    }
    return SUCCESSFUL_EXIT;
}

/*Функция для нахождения последнего индекса.
Принимает указатель на начало массива и указатель на его конец.
Возвращает указатель позиции нового конца.*/
int *find_endpoint(int *pointer_begin, int *pointer_end)
{
    int *pointer_current = pointer_begin;
    while (pointer_current < pointer_end)
    {
        if (*pointer_current < 0)
            return ++pointer_current;
        pointer_current++;
    }
    return pointer_current;
}

/*Остатки прошлого
Функция, которая считает по формуле из условия
Принимает указатели на начало и конец массива
Возвращает результат
int formula(int *pointer_begin, int *pointer_end)
{
    int result = 1;
    int *pointer_current = pointer_begin;
    while (pointer_current < pointer_end) 
    {
        result *= *pointer_current;
        pointer_current++;
    }
    return result;
}
*/

/*Функция для счета значения по формуле.
Принимает указатель на начало массива и указатель за конец массива.
Возвращает результат счета.*/
int compute(int *pointer_begin, int *pointer_end)
{
    int result = 0;
    int *pointer_current = pointer_begin;
    int current_value = *pointer_current;

    while (pointer_current < pointer_end)
    {
        pointer_current++;
        result += current_value;
        current_value *= *pointer_current;
    }
    return result;
}


int main(void)
{
    size_t size;
    int arr[ARRAY_MAX_SIZE];

    printf("Input size of array: ");
    if (scanf("%zu", &size) != 1)
    {
        printf("Incorrect input");
        return INCORECT_INPUT;
    }
    if (0 == size || size > ARRAY_MAX_SIZE)
    {
        printf("Incorrect size input");
        return INCORRECT_SIZE_INPUT;
    }

    printf("Input elements in array: \n");
    int *pa = arr, *pe = pa + size;
    if (array_input(pa, pe) != 0)
    {
        printf("Incorrect input");
        return INCORECT_INPUT;
    }

    int *ps = find_endpoint(pa, pe);
    int result = compute(pa, ps);
    printf("Result = %d", result);
    return SUCCESSFUL_EXIT;
}
