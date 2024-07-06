#ifndef H_LOGIC
#define H_LOGIC

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include "errorcode.h"

#define WORDS 10
#define MAX_STRLEN (256 + 1)
#define MAX_WORD_SIZE (16 + 1)
#define DELIM " \n\t.,!?"
#define OPERATOR_NUMBERS 3
#define COUNTRY_CODE_EMPTY 1
#define COUNTRY_CODE_VALID 2
#define COUNTRY_CODE_ERROR 3

/**
 * @brief Функция для проверки кода страны
 * 
 * @param[in] buf Строка с номером телефона
 * @param[in] size Размер строки
 * @param[in,out] index Индекс начала строки (откуда начинаем проверять)
 * 
 * @returns
 * Код ситуации: 1 - без кода страны (валидно), 2 - с кодом страны (валидно), 3 - без кода страны (невалидно)
*/
int is_code_contry_valid(const char *buf, size_t size, size_t *index);

/**
 * @brief Функция для проверки оператора страны
 * 
 * @param[in] buf Строка с номером телефона
 * @param[in] size Размер строки
 * @param[in,out] index Индекс начала строки (откуда начинаем проверять)
 * 
 * @returns
 * Правда или ложь
*/
bool is_code_operator_valid(const char *buf, size_t size, size_t *index);

/**
 * @brief Функция для проверки цифр после оператора в номере
 * 
 * @param[in] buf Строка с номером телефона
 * @param[in] size_string Размер строки
 * @param[in] size_of_numbers Размер чисел, которые мы должны валидировать
 * @param[in,out] index Индекс начала строки (откуда начинаем проверять)
 * 
 * @returns
 * Правда или ложь
*/
bool is_numbers_valid(const char *buf, size_t size_string, size_t size_of_numbers, size_t *index);

/**
 * @brief Функция для проверки номера
 * 
 * @param[in] buf Строка с номером телефона
 * @param[in] size Размер строки
 * 
 * @returns
 * Правда или ложь
*/
bool is_number(const char *buf, size_t size);

#endif
