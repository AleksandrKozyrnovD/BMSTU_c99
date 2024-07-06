#ifndef __READSTR_H__
#define __READSTR_H__

#include <stdio.h>
#include "list.h"
#include "errors.h"


/**
 * @brief Функция считывания строки в развернутый список (Да, так написано в условии - развернутый список)
 *
 * @details Создает (выделяет память на) при каждом вызове!
 *
 * @param[in] file Файловый указатель
 * @param[out] head Указатель на голову
 * @return Код ошибки
 */
errors_t readstr(FILE *file, node_t **head);

#endif

