#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <stdio.h>
#include "errors.h"


typedef struct student_t
{
    char *name; //Фамилия с неограниченным кол-вом символов
    int mark;
} student_t;

/**
 * @brief Функция чтения студента из файла.
 *
 * @details Считается, что на указателе на структуру память уже выделена
 *
 * @param[in] file Файл
 * @param[out] student Указатель на структуру студентов
 * @return Код ошибки
 */
errors_t student_read(FILE *file, student_t *student);

/**
 * @brief Функция чтения студента из файла.
 *
 * @details Считается, что на указателе на структуру память еще НЕ выделена
 *
 * @param[in] file Файл
 * @param[out] student Указатель на структуру студентов
 * @return Код ошибки
 */
errors_t student_read_ex(FILE *file, student_t **student);

/**
 * @brief Функция печати студента в файл
 *
 * @param[in] file Файл
 * @param[in] student Указатель на структуру студента
 */
void student_print(FILE *file, const student_t *student);

/**
 * @brief Функция сравнения студентов (нестрогая)
 * 
 * @details Если оценки равны, сравнивается фамилия
 *
 * @param[in] left Указатель на левого
 * @param[in] right Указатель на правого
 * @return Численная разница
 */
int student_cmp(const void *left, const void *right);

/**
 * @brief Функция сравнения студентов (строгая)
 * 
 * @details Сравниваются только оценки
 *
 * @param[in] left Указатель на левого
 * @param[in] right Указатель на правого
 * @return Численная разница
 */
int student_cmp_explicit(const void *left, const void *right);

/**
 * @brief Функция заполнения и выделения памяти структуры студента
 *
 * @param[in] name Указатель на его фамилию
 * @param[in] mark Оценка
 * @return Указатель на динамически выделенную структуру студента
 */
student_t *student_create(char *name, int mark);

/**
 * @brief Освобождение памяти из-под студента и его полей
 *
 * @param[in] student Указатель на структуру студента
 */
void student_free(student_t *student);

#endif

