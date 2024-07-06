#ifndef H_IO
#define H_IO

#include "logic.h"

/*Функция для проверки корректности ввода
Принимает буфер, в который будет записана строка, и его максимальный размер
Возвращает код ошибки*/
int get_line(char *buf, size_t buf_size);

#endif