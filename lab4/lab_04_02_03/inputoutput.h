#ifndef H_IO
#define H_IO

#include "logic.h"

/*Функция для проверки корректности ввода
Принимает буфер, в который будет записана строка, и его максимальный размер
Возвращает код ошибки*/
int get_line(char *buf, size_t buf_size);

/*Функция, которая будет печатать только уникальные слова из двух строк
Принимает массивы слов и их размеры
Возвращает код ошибки*/
int print_uniq(char words1[][MAX_WORD_SIZE], size_t size1, char words2[][MAX_WORD_SIZE], size_t size2);

/*Функция, проверяющая уникальность слова в двух строках
Принимает массивы слов и их размеры, слово и его номер в строке
Возвращает правду или ложь*/
// bool is_uniq(char array_words1[][MAX_WORD_SIZE], size_t size1, char array_words2[][MAX_WORD_SIZE], size_t size2, const char word[MAX_WORD_SIZE], size_t word_index);
bool is_uniq(char array_words[][MAX_WORD_SIZE], size_t size, const char word[MAX_WORD_SIZE], bool mine);

#endif