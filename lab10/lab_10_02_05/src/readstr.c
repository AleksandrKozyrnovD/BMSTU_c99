#include "readstr.h"
#include "errors.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Проверка на содержание '\n', а также его удаление
 *
 * @param[in,out] buf Указатель на буфер
 * @return Правда или ложь
 */
static int is_slash_n(char *buf)
{
    for (size_t i = 0; i < N && buf[i]; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            return 1;
        }
    return 0;
}

errors_t readstr(FILE *file, node_t **head)
{
    if (!file || !head)
        return ERR_ARGS;

    *head = node_create();
    
    char buf[N + 1];
    // memset(buf, 1, (N + 1) * sizeof(char)); //Инициализация нулями

    node_t *node = *head;
    int is_empty = 1;
    while (fgets(buf, sizeof(buf), file))
    {
        if (*buf == '\n' || !*buf)
        {
            node->next = NULL;
            break;
        }
        is_empty = 0;
        if (is_slash_n(buf) == 1)
        {
            memcpy(node->str, buf, strlen(buf) * sizeof(char));
            // printf("Strlen = %zu\n", strlen(buf));
            node->str[strlen(buf)] = 0;
            node->next = NULL;
            break;
            // return EXIT_SUCCESSFUL;
        }
        else
        {
            memcpy(node->str, buf, N * sizeof(char));
            node->next = node_create();
            if (!node->next)
                return ERR_MEM;
            node = node->next;
        }
        //Очистка буфера
        // memset(buf, 0, (N + 1) * sizeof(char));
    }
    
    if (is_empty)
    {
        node_free(node);
        *head = NULL;
        return ERR_EMPTY;
    }
    // for (node_t *temp = *head; temp; temp = temp->next)
    // {
    //     for (size_t i = 0; i < N && temp->str[i]; i++)
    //     {
    //         printf("(%c,%d) ", temp->str[i], temp->str[i]);
    //     }
    // }
    // printf("\n");

    return EXIT_SUCCESSFUL;
}

