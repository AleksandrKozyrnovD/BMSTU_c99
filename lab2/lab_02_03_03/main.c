#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SUCCESSFUL_EXIT 0
#define INCORECT_INPUT 1
#define INCORRECT_SIZE_INPUT 2
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

/*Функция для вставки элемента в массив.
Принимает указатель на начало массива, указатель на его длину, число и позицию, на которую ее нужно вставить.
Ничего не возвращает.*/
void insert(int *array, size_t *size, int number, size_t position)
{
    *size = *size + 1;
    for (size_t i = *size; i > position; i--)
    {
        array[i] = array[i - 1];
    }
    array[position] = number;
}

/*Функция для перевертывания числа.
Принимает само число.
Возвращает перевернутое число.*/
int reverse_number(int number)
{
    int result = 0;
    do
    {
        result *= 10;
        result += number % 10;
        number /= 10;
    }
    while (number);

    return result;
}

/*Функция для вставки в массиве после каждого положительного числа его перевернутое число.
Принимает указатель на начало массива и указатель на его размер.
Ничего не возвращает*/
void reshape_array(int *array, size_t *size)
{
    size_t i = 0;
    while (i < *size)
    {
        if (array[i] > 0)
        {
            insert(array, size, reverse_number(array[i]), i + 1);
            i++;
        }
        i++;
    }
}


int main(void)
{
    size_t size;
    int arr[2 * ARRAY_MAX_SIZE];

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
    if (array_input(arr, size) != 0)
    {
        printf("Incorrect input");
        return INCORECT_INPUT;
    }

    reshape_array(arr, &size);
    print_array(arr, size);

    return SUCCESSFUL_EXIT;
}
