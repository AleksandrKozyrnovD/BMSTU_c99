#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "list.h"
#include "fileread.h"
#include "node.h"
#include "student.h"


/*
 * Задача:
 * В файле хранятся студенты. У студентов есть фамилия и оценка.
 * В зависимости от указанных ключей, либо отсортировать список студентов, либо вставить
 * после студента с самой минимальной оценкой студента с самой максимальной оценкой.
 *
 * Студенты в файле располагаются так: "Оценка Фамилия"
 *
 * Правила добавления студентов в список:
 * Если у прочитанного студента средняя оценка выше или равна оценке первого студента,
 * то такой студент вставляется в конец списка. Если его оценка ниже, то вставляется в начало.
 *
 * Использование:
 * app.exe [s,i,p] filein fileout
 *
 * [s,i] - опция
 * - s - отсортировать текущий лист
 * - i - вставить максимальный элемент перед минимальным
 * - p - просто вывести список
 * 
 * filein - входной файл
 * fileout - выходной файл
 * */

int main(int argc, char **argv)
{
    errors_t rc = EXIT_SUCCESSFUL;
    if (argc != 4)
        return ERR_ARGS;
    
    node_t *head = NULL;
    student_t *buffer = NULL;
    size_t buffer_size = 0;

    FILE *filein = NULL, *fileout = NULL;
    
    filein = fopen(argv[2], "r");
    if (!filein)
        rc = ERR_FILE;
    if (!rc)
    {
        fileout = fopen(argv[3], "w");
        if (!fileout)
            rc = ERR_FILE;
    }
    
    if (!rc)
    {
        rc = create_buffer(filein, &buffer, &buffer_size);
        if (!rc)
        {
            rc = read_into_list(buffer, buffer_size, &head);
            if (!rc)
            {
                if (strcmp(argv[1], "s") == 0)
                    head = sort(head, student_cmp);
                else if (strcmp(argv[1], "i") == 0)
                {
                    node_t *tmp = find_maximum_node(head);
                    node_t *max = node_create(tmp->data);
                    if (!max)
                        rc = ERR_MEM;
                    else
                        insert(&head, max, head);
                }
                else if (strcmp(argv[1], "p") != 0)
                    rc = ERR_ARGS;

                if (!rc)
                    list_print(fileout, head, node_print);
            }
        }
    }
    
    if (filein)
        fclose(filein);
    if (fileout)
        fclose(fileout);

    list_free(head);
    buffer_free(buffer, buffer_size);


    return rc;
}

