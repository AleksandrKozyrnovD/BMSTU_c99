#ifndef __FILEREAD_H__
#define __FILEREAD_H__

#include <stdio.h>
#include <stddef.h>
#include "errors.h"
#include "list.h"
#include "student.h"

/**
 * @brief Создание места под хранение структур
 *
 * @param[in] file Файл, откуда происходит считывание
 * @param[out] buffer Массив студентов
 * @param[out] size Размер массив студентов
 * @return Код ошибки
 */
errors_t create_buffer(FILE *file, student_t **buffer, size_t *size);

/**
 * @brief Считывание всех студентов по правилу в список
 *
 * @param[in] buffer Место, откуда считываются студенты
 * @param[in] size Размер буфера
 * @param[out] head Указатель на голову списка
 * @return Код ошибки
 */
errors_t read_into_list(student_t *buffer, size_t size, node_t **head);

/**
 * @brief Очистить буфер
 *
 * @param[in] buffer Буфер
 * @param[in] size Его размер
 */
void buffer_free(student_t *buffer, size_t size);

/**
 * @brief Найти наибольший по ключу узел списка
 *
 * @param[in] head Указатель на голову
 * @return Указатель на наибольший узел (Или NULL, если нет списка вовсе)
 */
node_t *find_maximum_node(node_t *head);

#endif

