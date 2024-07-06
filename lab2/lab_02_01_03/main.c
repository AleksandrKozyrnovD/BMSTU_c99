#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#define SUCCESSFUL_EXIT 0
#define INCORECT_INPUT 1
#define INCORRECT_SIZE_INPUT 2
#define NO_POSITIVE 3
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

/*Функция, считающая среднее геометрическое из всех положительных элементов массива.
Принимает указатель на начало масссива, его длину и указатель на переменную, которая будет хранить результат.
Возвращает код ошибки.*/
int geometric_mean_positive(int *const array, size_t array_lenght, double *result)
{
    size_t power = 0;
    int multiplication_result = 1;

    for (size_t i = 0; i < array_lenght; i++)
    {
        if (array[i] > 0)
        {
            power++;
            multiplication_result *= array[i];
        }
    }

    if (power != 0)
    {
        *result = pow(multiplication_result, 1.0 / power);
        return SUCCESSFUL_EXIT;
    }
    else
        return NO_POSITIVE;
}


int main(void)
{
    size_t size;
    double result;
    int arr[ARRAY_MAX_SIZE], return_code;

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

    return_code = geometric_mean_positive(arr, size, &result);
    
    switch (return_code)
    {
        case SUCCESSFUL_EXIT:
            printf("Geometric mean = %lf", result);
            return SUCCESSFUL_EXIT;
        case NO_POSITIVE:
            printf("No pisitive numbers found");
            return NO_POSITIVE;   
    }
}
