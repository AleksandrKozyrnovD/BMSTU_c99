#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include "node.h"
#include "errors.h"

typedef void (*printnode)(FILE *, const node_t *);

typedef int (*comparator)(const void *, const void *);

/**
 * @brief Функция вставки нового узла в голову списка
 *
 * @param[in] head Указатель на голову списка
 * @param[in] node Указатель на вставляемый узел
 * @return Указатель на новую голову
 */
node_t *push_front(node_t *head, node_t *node);

/**
 * @brief Функция вставки нового узла в хвост списка
 *
 * @param[in] head Указатель на голову списка
 * @param[in] node Указатель на вставляемый узел
 * @return Указатель на новую голову
 */
node_t *push_end(node_t *head, node_t *node);

/**
 * @brief Функция удаления головного узла списка и возвращение его информационной части
 *
 * @param[in,out] head Указатель на голову
 * @return Указатель на информационную часть удаленного узла
 */
char *pop_front(node_t **head);

/**
 * @brief Функция удаления хвостового узла списка и возвращение его информационной части
 *
 * @param[in,out] head Указатель на голову
 * @return Указатель на информационную часть удаленного узла
 */
char *pop_end(node_t **head);

/**
 * @brief Функция вставки нового узла перед указанным
 *
 * @param[in,out] head Указатель на голову списка
 * @param[in] elem Указатель на вставляемый узел
 * @param[in] before Указатель на узел, перед которым нужно вставить узел
 */
void insert(node_t **head, node_t *elem, node_t *before);

/**
 * @brief Освобождение памяти из-под узлов (но не из-под их информационной части)
 *
 * @param[in] head Указатель на голову списка
 */
void list_free(node_t *head);

/**
 * @brief Функция склеивания двух списков
 *
 * @param[in,out] head_a Указатель на голову списка, к которому присоединяется второй список
 * @param[in,out] head_b Указатель на присоединяемую голову второго списка
 */
void append(node_t **head_a, node_t **head_b);

/**
 * @brief Функция печати развернутого списка
 *
 * @param[in] file Файловый указатель
 * @param[in] head Голова списка
 */
void list_print(FILE *file, const node_t *head);

/**
 * @brief Соединение двух строк
 *
 * @param[in,out] head_a Указатель на левую голову. Результат будет сохранен в эту голову
 * @param[in,out] head_b Указатель на правую голову. После функции будет указывать в NULL
 */
void concat_str(node_t **head_a, node_t **head_b);

/**
 * @brief Функция для нахождение подстроки в строке
 *
 * @param[in] head_a Голова строки поиска
 * @param[in] head_b Голова искомой подстроки
 * @param[out] pos Указатель на позицию, в которой начинается подстрока
 * @return Код ошибки
 */
errors_t find_str(const node_t *head_a, const node_t *head_b, size_t *pos);

/**
 * @brief Убирает каждое вхождение ch из строки и заменяет ее на NULL
 *
 * @param[in,out] head Указатель на голову
 * @param[in] ch Удалаемый символ
 */
void remove_char(node_t *head, char ch);

/**
 * @brief Удаляет повторяющиеся вхождения символа, если они идут друг за другом
 *
 * @details Пример: "asd    asd", удаляем ' ' --> "asd asd"
 *
 * @param[in,out] head Указатель на голову
 * @param[in] ch Удаляемый символ
 */
void reduce_char(node_t *head, char ch);

/**
 * @brief Функция сжатия развернутого списка
 *
 * @param[in,out] head Указатель на голову
 */
void compact(node_t *head);

#endif

