#ifndef H_LOGIC
#define H_LOGIC

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "errorcode.h"

#define MAX_STRLEN (256 + 1)
#define MAX_COUNT_WORDS 125
#define MAX_WORD_SIZE (16 + 1)
#define DELIM " ,;:-.?!"

/*Функция, которая будет брать следующее слово в строке
Принимает строку, указатель на указатели начала и конца
Ничего не возвращает*/
void get_next_word(char *string, char **pbegin, char **pend);

/*Функция для копирования слова по двум указателям
Принимает указатель начала и конца, слово, в которое будет записан результат, и его размер
Возвращает код ошибки*/
int copy_word(char *pbegin, char *pend, char *word, size_t word_size);

/*Функция, проверяющая уникальность слова в двух строках
Принимает массивы слов и их размеры, слово и его номер в строке
Возвращает правду или ложь*/
// bool is_uniq(char array_words1[][MAX_WORD_SIZE], size_t size1, char array_words2[][MAX_WORD_SIZE], size_t size2, const char word[MAX_WORD_SIZE], size_t word_index);

/*Функция для формирования массива слов из строки
Принимает саму строку, массив слов и размер массива слов по указателю
Возвращает код ошибки*/
int parse_string(char *string, char result[][MAX_WORD_SIZE], size_t *size);


#endif
