#include "fileread.h"
#include "errors.h"
#include "list.h"
#include "node.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Функция подсчета студентов в файле
 *
 * @param[in] file Указатель на файл
 * @return Количество студентов
 */
static size_t count_students(FILE *file)
{
    errors_t rc = EXIT_SUCCESSFUL;
    student_t stud = { .name = NULL, .mark = 0 };
    size_t count = 0;

    while (!rc)
    {
        rc = student_read(file, &stud);
        if (!rc)
        {
            free(stud.name);
            count++;
        }
    }

    return count;
}

/**
 * @brief Функция считывания студентов в буфер с файла
 *
 * @param[in] file Указатель на файл
 * @param[out] buffer Указатель на буффер
 * @param[in] size Размер буффера
 * @return Код ошибки
 */
static errors_t read_buffer(FILE *file, student_t *buffer, size_t size)
{
    errors_t rc = EXIT_SUCCESSFUL;
    for (size_t i = 0; i < size && !rc; i++)
    {
        rc = student_read(file, buffer + i);
        if (rc)
            buffer_free(buffer, i);
    }

    return rc;
}

errors_t create_buffer(FILE *file, student_t **buffer, size_t *size)
{
    *size = count_students(file);

    if (!(*size))
        return ERR_EMPTY;

    *buffer = malloc(*size * sizeof(student_t));
    if (!(*buffer))
    {
        *size = 0;
        return ERR_MEM;
    }
    
    rewind(file);
    return read_buffer(file, *buffer, *size);
}

void buffer_free(student_t *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
        free(buffer[i].name);
    free(buffer);
}

node_t *find_maximum_node(node_t *head)
{
    if (!head)
        return NULL;

    node_t *max = head;
    head = head->next;

    while (head)
    {
        if (student_cmp_explicit(max->data, head->data) < 0)
            max = head;
        head = head->next;
    }
    
    return max;
}

errors_t read_into_list(student_t *buffer, size_t size, node_t **head)
{
    node_t *ptr = NULL;
    errors_t rc = EXIT_SUCCESSFUL;

    for (size_t i = 0; i < size && !rc; i++)
    {
        ptr = node_create(buffer + i);
        if (!ptr)
            rc = ERR_MEM;
        
        if (!rc && !(*head))
            *head = push_front(*head, ptr);
        else if (!rc && student_cmp((*head)->data, ptr->data) > 0)
            *head = push_front(*head, ptr);
        else if (!rc)
            *head = push_end(*head, ptr);
    }

    return rc;
}

