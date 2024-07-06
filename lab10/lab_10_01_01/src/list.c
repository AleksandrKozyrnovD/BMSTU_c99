#include "list.h"
#include "errors.h"
#include "node.h"

node_t *push_front(node_t *head, node_t *node)
{
    if (!head || !node)
        return node;

    node->next = head;

    return node;
}

node_t *push_end(node_t *head, node_t *node)
{
    if (!head)
        return node;
    
    node_t *tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;

    return head;
}

void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
    {
        return NULL;
    }
    
    node_t *tmp = *head;
    void *data = tmp->data;
    *head = (*head)->next;
    node_free(tmp);
    // if ((*head)->next)
    // {
    //     *head = (*head)->next;
    //     node_free(tmp);
    // }
    // else
    // {
    //     node_free(tmp);
    //     *head = NULL;
    //     // (*head)->next = NULL;
    // }

    return data;
}

void *pop_back(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;
    void *data = NULL;
    if (!(*head)->next)
    {
        data = (*head)->data;
        node_free(*head);
        *head = NULL;
    }
    else
    {
        node_t *tmp = *head;
        /*
        Конец условия такой, потому что нам нужно знать предыдущий узел перед удаляемым (предпоследний в нашем случае)
        Так нам не понадобится проходить список еще раз
        */
        while (tmp->next->next)
            tmp = tmp->next;
        node_t *back = tmp->next;
        data = back->data;
        tmp->next = NULL;
        node_free(back);
    }

    return data;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (!*head && !before)
        *head = elem;
    else if (*head == before)
        *head = push_front(*head, elem);
    else
    {
        node_t *tmp = *head;
        while (tmp->next != before && tmp->next)
            tmp = tmp->next;
        if (tmp->next == before)
        {
            elem->next = before;
            tmp->next = elem;
        }
    }
}


void list_print(FILE *file, const node_t *head, printnode print)
{
    while (head)
    {
        print(file, head);
        head = head->next;
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

errors_t list_copy(node_t *head, node_t **newhead)
{
    if (!newhead)
        return ERR_ARGS;

    if (!head)
    {
        *newhead = NULL;
        return EXIT_SUCCESSFUL;
    }
    
    node_t *tmp = NULL;
    node_t *copy = NULL;
    while (head)
    {
        tmp = node_create(head->data);
        if (!tmp)
        {
            list_free(copy);
            return ERR_MEM;
        }
        if (!copy)
            copy = tmp;
        else
        {
            copy->next = tmp;
            copy = copy->next;
        }
        // *newhead = push_end(*newhead, tmp);
        head = head->next;
    }

    return EXIT_SUCCESSFUL;
}

void append(node_t **head_a, node_t **head_b)
{
    if (!head_a || !head_b)
        return;

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

void front_back_split(node_t *head, node_t **back)
{
    if (!back)
        return;
    
    if (!head)
    {
        *back = NULL;
        return;
    }
    node_t *fast = head;
    node_t *half = head;
    node_t *before = NULL;
    if (!head->next)
    {
        *back = NULL;
        return;
    }

    while (fast)
    {
        if (fast)
        {
            before = half;
            half = half->next;
            fast = fast->next;
        }
        if (fast)
            fast = fast->next;
    }
    
    if (before)
        before->next = NULL;
    *back = half;
}

/**
 * @brief Подфункция сортировки слиянием
 *
 * @details Вызывает саму себя до тех пор, пока не кончатся оба подсписка.
 *
 * @param[in,out] head_a Сортируемый левый подсписок
 * @param[in,out] head_b Сортируемый правый подсписок
 * @param[in] cmp Сравнитель
 * @return Указатель на новый узел
 */
node_t *sorted_merge(node_t **head_a, node_t **head_b, comparator cmp)
{
    if (!head_a || !head_b || !cmp)
        return NULL;
    node_t *res = NULL;
    node_t *tmp = NULL;
    
    if (!*head_a)
    {
        res = push_front(res, *head_b);
        *head_b = NULL;
        return res;
    }
    else if (!*head_b)
    {
        res = push_front(res, *head_a);
        *head_a = NULL;
        return res;
    }
    // if (*head_a == NULL)
    //     return *head_b;
    // else if (*head_b == NULL)
    //     return *head_a;
    
    int cmp_score = cmp((*head_a)->data, (*head_b)->data);
    if (cmp_score <= 0)
    {
        res = push_front(res, *head_a);
        tmp = (*head_a)->next;
        (*head_a)->next = NULL;
        res->next = sorted_merge(&tmp, head_b, cmp);
    }
    else
    {
        res = push_front(res, *head_b);
        tmp = (*head_b)->next;
        (*head_b)->next = NULL;
        res->next = sorted_merge(head_a, &tmp, cmp);
    }
    // if (cmp_score <= 0)
    // {
    //     res = *head_a;
    //     res->next = sorted_merge(&(*head_a)->next, head_b, cmp);
    // }
    // else
    // {
    //     res = *head_b;
    //     res->next = sorted_merge(head_a, &(*head_b)->next, cmp);
    // }
    
    *head_a = NULL;
    *head_b = NULL;
    return res;
}

node_t *sort(node_t *head, comparator cmp)
{
    if (!head || !head->next)
        return head;
    node_t *back = NULL;
    front_back_split(head, &back);

    head = sort(head, cmp);
    back = sort(back, cmp);

    return sorted_merge(&head, &back, cmp);
}

