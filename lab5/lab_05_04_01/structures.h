#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <stdint.h>
#include "errorcode.h"

#define FAMILY_LEN 25
#define NAME_LEN 10
#define N_MARKS 4

typedef struct
{
    char familia[FAMILY_LEN + 1];
    char name[NAME_LEN + 1];
    uint32_t marks[N_MARKS];
} student_t;

/**
 * @brief Функция для чтения студента из текстового файла
 * 
 * @param[in] file Файловый указатель
 * @param[out] student Студент
 * 
 * @returns
 * Код ошибки
*/
int read_student(FILE *file, student_t *student);

/**
 * @brief Функция для печати студента в файл
 * 
 * @param[in] file Файловый указатель
 * @param[in] student Студент
 * 
 * @returns
 * Ничего
*/
void print_student(FILE *file, const student_t *student);

/**
 * @brief Функция для сравнения студентов по фамилии
 * 
 * @param[in] left Студент 1
 * @param[in] right Студент 2
 * 
 * @returns
 * Возвращает больше нуля, если первый студент больше второго, иначе меньше нуля, иначе ноль, если равны
*/
int cmp_by_family_stud(const student_t *left, const student_t *right);

/**
 * @brief Функция для сравнения студентов по имени
 * 
 * @param[in] left Студент 1
 * @param[in] right Студент 2
 * 
 * @returns
 * Возвращает больше нуля, если первый студент больше второго, иначе меньше нуля, иначе ноль, если равны
*/
int cmp_by_name_stud(const student_t *left, const student_t *right);

#endif
