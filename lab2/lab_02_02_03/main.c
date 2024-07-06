#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define SUCCESSFUL_EXIT 0
#define INCORECT_INPUT 1
#define INCORRECT_SIZE_INPUT 2
#define NO_ARMSTRONG_NUMBERS 3
#define ARRAY_MAX_SIZE 10

/*Функция для заполнения массива.
Принимает указатель на начало массива и длину массива.
Возвращает код ошибки.*/
int array_input(int *array, size_t array_lenght)
{
    for (size_t i = 0; i < array_lenght; i++)
    {
        if (scanf("%d", &array[i]) != 1)
        {
            return INCORECT_INPUT;
        }
    }
    return SUCCESSFUL_EXIT;
}

/*Функция для печати массива.
Принимает указатель на начало массива и его длину.
Ничего не возвращает.*/
void print_array(int *const array, size_t array_lenght)
{
    printf("Array:\n");
    for (size_t i = 0; i < array_lenght; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

/* Функция проверки числа Армстронга.
Принимает целочисленное число old_number.
Возвращает 1, если число является числом Армстронга, иначе 0. */
bool is_armstrong(int old_number)
{
    int number;
    int result = 0;
    size_t size_of_number = 0;

    number = abs(old_number);

    do
    {
        size_of_number++;
        number /= 10;
    } while (number);

    number = abs(old_number);
    while (number)
    {
        int mult = 1;
        for (size_t i = 0; i < size_of_number; i++)
            mult *= number % 10;
        result += mult;
        number /= 10;
    }

    return result == old_number;
}

/*Функция, создающая новый массив на основе старого, который будет состоять только из чисел Армстронга.
Принимает указатели на начало двух массивов, размер старого и указатель на размер нового.
Возвращает код ошибки.*/
int copy_elements_to_new_arr(int *old_array, size_t old_size, int *new_array, size_t *new_size)
{
    for (size_t i = 0; i < old_size; i++)
    {
        if (is_armstrong(old_array[i]))
        {
            new_array[*new_size] = old_array[i];
            (*new_size)++;
        }
    }
    if (*new_size == 0)
    {
        return NO_ARMSTRONG_NUMBERS;
    }
    return SUCCESSFUL_EXIT;
}


int main(void)
{
    size_t old_size, new_size = 0;
    int old_array[ARRAY_MAX_SIZE], new_array[ARRAY_MAX_SIZE];

    printf("Input size of array: ");
    if (scanf("%zu", &old_size) != 1)
    {
        printf("Incorrect input");
        return INCORECT_INPUT;
    }
    if (0 == old_size || old_size > ARRAY_MAX_SIZE)
    {
        printf("Incorrect size input");
        return INCORRECT_SIZE_INPUT;
    }

    printf("Input elements in array: \n");
    if (array_input(old_array, old_size) != 0)
    {
        printf("Incorrect input");
        return INCORECT_INPUT;
    }

    if (copy_elements_to_new_arr(old_array, old_size, new_array, &new_size) != SUCCESSFUL_EXIT)
    {
        printf("No armstrong numbers found");
        return NO_ARMSTRONG_NUMBERS;
    }

    print_array(new_array, new_size);
    return SUCCESSFUL_EXIT;
}
