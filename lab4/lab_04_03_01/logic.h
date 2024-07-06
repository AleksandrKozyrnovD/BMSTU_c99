#ifndef H_LOGIC
#define H_LOGIC

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include "errorcode.h"

#define MAX_STRLEN (256 + 1)
#define MAX_WORD_SIZE (16 + 1)
#define DELIM " ,;:.-?!"


/*Функция, которая будет брать следующее слово в строке
Принимает строку, указатель на указатели начала и конца
Ничего не возвращает*/
// void get_next_word(char *string, char **pbegin, char **pend);
char *get_next_word(void);

/*Функция для копирования слова по двум указателям
Принимает указатель начала и конца, слово, в которое будет записан результат, и его размер
Возвращает код ошибки*/
int copy_word(char *pbegin, const char *pend, char *word, size_t word_size);

/*Функция для формирования массива слов из строки
Принимает саму строку, массив слов и размер массива слов по указателю
Возвращает код ошибки*/
// int parse_string(char *string, char result[][MAX_WORD_SIZE], size_t *size);
int parse_string(char *string, char result[][MAX_WORD_SIZE], size_t *count);

/*Функция, которая оставляет только первое вхождение каждой буквы
Принимает строчку
Возвращает код ошибки*/
int left_only_uniq_chars(char *string);

/*Функция, формирующая строчку из массива слов
Принимает массив слов и его длину, саму строчку и ее максимальный размер
Возвращает код ошибки*/
int form_string(char words[][MAX_WORD_SIZE], size_t word_count, char buffer[], size_t buffer_size);

#endif
