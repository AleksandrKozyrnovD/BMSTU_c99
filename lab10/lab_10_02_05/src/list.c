#include "list.h"
#include "errors.h"
#include "node.h"
#include <stdio.h>
#include <string.h>

node_t *push_front(node_t *head, node_t *node)
{
    if (!head || !node)
        return node;

    node->next = head;

    return node;
}

node_t *push_end(node_t *head, node_t *node)
{
    if (!head || !node)
        return node;
    
    node_t *tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;

    return head;
}

char *pop_front(node_t **head)
{
    if (*head == NULL || head == NULL)
        return NULL;
    
    node_t *tmp = *head;
    char *data = tmp->str;
    *head = tmp->next;
    node_free(tmp);

    return data;
}

char *pop_end(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;
    char *data = NULL;
    if (!(*head)->next)
    {
        data = (*head)->str;
        node_free(*head);
        *head = NULL;
    }
    else
    {
        node_t *tmp = *head;
        while (tmp->next->next)
            tmp = tmp->next;
        node_t *back = tmp->next;
        data = back->str;
        tmp->next = NULL;
        node_free(back);
    }

    return data;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (*head == before)
        *head = push_front(*head, elem);
    else
    {
        node_t *tmp = *head;
        while (tmp->next != before)
            tmp = tmp->next;
        elem->next = before;
        tmp->next = elem;
    }
}

void list_free(node_t *head)
{
    if (!head)
        return;
    node_t *tmp = head;
    // head = head->next;
    while (tmp)
    {
        head = head->next;
        node_free(tmp);
        tmp = head;
    }
}

void append(node_t **head_a, node_t **head_b)
{
    if (*head_a == NULL)
    {
        *head_a = *head_b;
    }
    else
    {
        node_t *end = *head_a;
        while (end->next)
            end = end->next;
        end->next = *head_b;
    }
    *head_b = NULL;
}

void list_print(FILE *file, const node_t *head)
{
    while (head)
    {
        // printf("\nPrinting\n");
        node_print(file, head);
        head = head->next;
    }
    printf("\n");
}

void concat_str(node_t **head_a, node_t **head_b)
{
    if (!*head_b)
        return;

    if (!*head_a)
    {
        *head_a = *head_b;
        *head_b = NULL;
        return;
    }

    node_t *tmp = *head_a;
    while (tmp->next)
        tmp = tmp->next;

    size_t offset = 0;
    for (; offset != N && tmp->str[offset]; offset++);
    
    node_t *back = *head_b;
    /*1,2,5,\0 + 3,4,5,6 + 7,8,9,\0 --> offset = 3 --> (1,2,5,3) V (4,5,6,7) V (8,9,\0,\0) */

    node_t *next = back->next;

    // Делаем 1 раз для конца первого списка с учетом единственного нуля
    if (!next)
    {
        size_t next_offset = 0;

        for (; next_offset != N && back->str[next_offset]; next_offset++);
        
        if (next_offset + 1 <= N - offset)
        {
            memcpy(tmp->str + offset, back, (next_offset + 1) * sizeof(char));
            node_free(back);
            tmp->next = NULL;
        }
        else
        {
            memcpy(tmp->str + offset, back->str, (N - offset) * sizeof(char));
            memcpy(back->str, back->str + (N - offset), (next_offset - offset + 1) * sizeof(char));
            tmp->next = back;
        }

        *head_b = NULL;
        return;
    }
    else
    {
        memcpy(tmp->str + offset, back, (N - offset) * sizeof(char));
        tmp->next = back;
    }
    while (next)
    {
        if (next->next)
        {
            memcpy(back->str, back->str + (N - offset), offset * sizeof(char));
            /* 3,4,5,6 --> 4,5,6,6 */

            memcpy(back->str + offset, next->str, (N - offset) * sizeof(char));
        }
        else
        {
            memcpy(back->str, back->str + (N - offset), offset * sizeof(char));
            /* 3,4,5,6 --> 4,5,6,6 */
            
            size_t next_offset = 0;

            for (; next_offset != N && next->str[next_offset]; next_offset++);

            if (next_offset + 1 <= N - offset)
            {
                memcpy(back->str + offset, next->str, (next_offset + 1) * sizeof(char));
                node_free(next);
                back->next = NULL;
            }
            else
            {
                memcpy(back->str + offset, next->str, (N - offset) * sizeof(char));
                memcpy(next->str, next->str + (N - offset), (next_offset - offset + 1) * sizeof(char));
            }
            break;
        }
        /* повторяем как с концом */
        back = next;
        next = next->next;
    }
    *head_b = NULL;
}

/**
 * @brief Функция проверки вхождения первого символа из искомой подстроки
 *
 * @param[in] a Указатель на узел строки, где происходит поиск
 * @param[in] b Указатель на узел искомой подстроки
 * @param[in] i Индекс в узле a
 * @return Правда или ложь
 */
static int test(const node_t *a, const node_t *b, size_t i)
{
    if (a->str[i] != b->str[0])
        return 1;
    return 0;
}

errors_t find_str(const node_t *head_a, const node_t *head_b, size_t *pos)
{
    if (!head_a || !head_b || !pos)
        return ERR_IO;
    
    int score = 0;
    const node_t *tmp = NULL;
    const node_t *curr = NULL;
    size_t zerooffset = 0, k = 0, j = 0, offset = 0;
    size_t minoffset = 0, position = 0;
    
    while (head_a)
    {
        /*

        Список А - список, в котором происходит поиск
        Список Б - список, который мы ищем в списке А

        k - Текущий индекс в узле списка А.
        j - Текущий индекс в узле списка Б.
        zerooffset - Первый нуль от левого края списка Б (его индекс)
        offset - Индекс первого совпавшего символа в списке А
         */
        k = 0;
        j = 0;
        zerooffset = 0;
        offset = 0;
        tmp = head_a;
        curr = head_b;
        
        //Текущий цикл находит первый совпавший символ списка А из списка Б (из списка Б при этом берется всегда первый символ)
        for (size_t i = 0; curr && i < N && tmp->str[i] && test(tmp, curr, offset); i++, offset++);
        
        // Если offset == N, то 1-го символа в списке А из списка Б нет
        // && curr - проверка на конец списка Б
        if (offset < N && curr)
        {
            // Ищем первый нуль из списка Б
            for (; zerooffset != N && curr->str[zerooffset]; zerooffset++);
            
            // Если нуль в списке Б встречен, то это, скорее всего, ее последний узел,
            // поэтому проверяем, хватает ли нам символов из списка А для полного сравнения
            // остатка списка Б и текущего остатка списка А
            //
            // Если это ложно, то идет обычная проверка
            if (zerooffset <= N - offset && zerooffset != N)
            {
                score = memcmp(curr->str, tmp->str + offset, zerooffset * sizeof(char));
                if (score)
                    return ERR_RANGE;
                *pos = position + offset;
                return EXIT_SUCCESSFUL;
            }
            else
                score = memcmp(curr->str, tmp->str + offset, (N - offset) * sizeof(char));
            
            // Изменение индексов в узлах списков
            j += N;
            k += N - offset;

            // Пока есть, что проверять из списка Б и текущий результат сравнения положительный (равен)
            while (curr && score == 0)
            {
                zerooffset = 0;
                // Два условия на обновление текущего узла
                if (j >= N)
                {
                    j -= N;
                    tmp = tmp->next;
                }
                if (k >= N)
                {
                    k -= N;
                    curr = curr->next;
                }
                //Проверка на существование узлов
                if (!curr || !tmp)
                    break;
                
                //Проверка на нули справа
                for (; zerooffset != N && curr->str[zerooffset]; zerooffset++);

                // Берем минимальное кол-во символов, которое можно проверить
                minoffset = (N - k) > (N - j) ? (N - j) : (N - k);

                //Конец строчки, в которой происходит поиск
                if (zerooffset <= minoffset && zerooffset != N)
                {
                    score = memcmp(curr->str + k, tmp->str + j, zerooffset * sizeof(char));
                    if (score)
                        break;
                    *pos = position + offset;
                    return EXIT_SUCCESSFUL;
                }
                //Иначе обычное сравнение
                score = memcmp(curr->str + k, tmp->str + j, minoffset);
                k += minoffset;
                j += minoffset;
            }
            //Если конец списка Б, то все верно
            if (!curr)
            {
                *pos = position + offset;
                return EXIT_SUCCESSFUL;
            }
        }
        //Обновление глобально головы списка А
        head_a = head_a->next;
        position += N;
    }

    return ERR_EMPTY;
}

void remove_char(node_t *head, char ch)
{
    while (head)
    {
        for (size_t i = 0; i < N; i++)
            if (head->str[i] == ch)
                head->str[i] = 0;
        head = head->next;
    }
}

void reduce_char(node_t *head, char ch)
{
    char lastchar = 0;

    node_t *temp = head;
    size_t index_temp = 0;
    while (head)
    {
        for (size_t i = 0; i < N && head->str[i]; i++)
        {
            if (head->str[i] == ch && lastchar == ch)
            {
                continue;
            }
            else
            {
                if (index_temp >= N)
                {
                    index_temp -= N;
                    temp = temp->next;
                }
                temp->str[index_temp] = head->str[i];
                index_temp++;
                lastchar = head->str[i];
            }
        }
        head = head->next;
    }
    if (index_temp == N)
    {
        temp->next->str[0] = 0;
        temp = temp->next;
    }
    else
        temp->str[index_temp] = 0;

    if (!temp || !temp->next)
        return;
    node_t *delete = temp->next;
    temp->next = NULL;
    temp = delete;
    while (delete)
    {
        delete = delete->next;
        node_free(temp);
        temp = delete;
    }
}

