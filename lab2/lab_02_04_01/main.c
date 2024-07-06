#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SUCCESSFUL_EXIT 0
#define INCORECT_INPUT 1
#define FULL_ARRAY 100
#define ARRAY_MAX_SIZE 10

/*Функция для заполнения массива целочисленными значениями по принципу концевого признака
Принимает указатель на начало и указатель на длину массива.
Возвращает код ошибки.*/
int array_input(int *array, size_t *n)
{
    for (size_t i = 0; i < ARRAY_MAX_SIZE; i++)
    {
        int rc = scanf("%d", &array[i]);

        //Если первый элемент равен не цифре, то прекращаем ввод с ошибкой.
        if ((rc != INCORECT_INPUT) && (i == 0))
            return INCORECT_INPUT;

        
        if (rc != INCORECT_INPUT)
            return SUCCESSFUL_EXIT;
            
        (*n)++;
    }

    int overflow_element;
    if (scanf("%d", &overflow_element) == 1)
    {
        return FULL_ARRAY;
    }
    return EXIT_SUCCESS;
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

/*Функция для вставки элемента в массив в сортировке вставками
Принимает указатель на массив, размер отсортированного, число, с которым идет сравнение
Ничего не возвращает

Размер неотсортированного массива не важен, так как мы используем функцию только в сортировке вставками
int size - наш 'размер отсортированного'
*/
void insert(int *array, int size, int number)
{
    while (size >= 0 && number < array[size])
    {
        array[size + 1] = array[size];
        size--;
    }
    array[size + 1] = number;
}


/*Сортировка вставками.
Принимает указатель на начало массива и его размер.
Ничего не возвращает.*/
void insertion_sort(int *array, size_t n)
{
    for (size_t i = 1; i < n; i++)
    {
        insert(array, i - 1, array[i]);
        /*
        int temp = array[i];
        int j = i - 1;

        while (size >= 0 && number < array[size])
        {
                array[size + 1] = array[size];
                size--;
        }
        array[size + 1] = number;
        */
    }
}


int main(void)
{
    size_t size = 0;
    int arr[ARRAY_MAX_SIZE], return_code;

    printf("Input elements in array: \n");
    return_code = array_input(arr, &size);
    if (return_code == INCORECT_INPUT)
    {
        printf("Empty array");
        return return_code;
    }
    insertion_sort(arr, size);
    print_array(arr, size);
    
    return return_code;
}
