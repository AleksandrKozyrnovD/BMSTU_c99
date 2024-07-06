#ifndef __LIB_H__
#define __LIB_H__

#include <stddef.h>

int generate_prime_numbers(long long *arr, size_t n);

/**
 * @brief Функция вставки нового элемента после каждого четного элемента число k
 * 
 * @param[in] original Исходный массив
 * @param[in] n Размер исходного массива
 * @param[out] new_array Массив, в который будут вставлены элементы k
 * @param[in] k Вставляемое число
 */
int insert_after_even(int *original, size_t n, int *new_array, size_t *k, int num);

#endif