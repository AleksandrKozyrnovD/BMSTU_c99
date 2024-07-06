#include <assert.h>
#include <check.h>
#include <stdlib.h>
#include "check_list.h"
#include "list.h"
#include "node.h"

static int intcmp(const void *l, const void *r)
{
    const int *le = l;
    const int *ri = r;

    return *le - *ri;
}

/**
 * @brief Function that creates node from element of array
 *
 * @param buffer Array
 * @param i Index in array (starting from 1)
 * @return Created node
 */
static node_t *read_node(int *const buffer, size_t i)
{
    assert(i != 0);
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp);
    
    tmp->data = buffer + i - 1;
    tmp->next = NULL;

    return tmp;
}

/**
 * @brief Functsia sozdania spiska iz massiva
 *
 * @param buffer Massiv
 * @param size Razmer massiva
 * @return Spisok
 */
static node_t *create_list(int *const buffer, size_t size)
{
    node_t *head = NULL;
    node_t *prev = NULL;
    node_t *tmp = NULL;
    for (size_t i = 0; i < size; i++)
    {
        tmp = read_node(buffer, i + 1);
        if (!head)
        {
            head = tmp;
            prev = head;
        }
        else
        {
            prev->next = tmp;
            prev = tmp;
        }
    }

    return head;
}

static void ck_assert_list_array_eq(node_t *head, int *buffer, size_t size)
{
    size_t i = 0;

    while (head)
    {
        ck_assert_int_eq(*(int *) head->data, buffer[i]);
        head = head->next;
        i++;
    }
    ck_assert_uint_eq(i, size);
}

//Dobavim tri elementa podryad
START_TEST(PushFront)
{
    int b[3] = { 1, 2, 3 };
    node_t *head = NULL;
    
    node_t *tmp = NULL;
    for (size_t i = 4; i != 1; i--)
    {
        tmp = read_node(b, i - 1);
        head = push_front(head, tmp);
        ck_assert(head == tmp);
    }
    
    ck_assert_list_array_eq(head, b, 3);

    list_free(head);
}
END_TEST

///Попробуем вставить три раза подряд узлы в конец
START_TEST(PushEnd)
{
    node_t *head = NULL;
    int b[3] = { 1, 2, 3 };

    node_t *tmp = read_node(b, 1);
    head = push_end(head, tmp);
    // ck_assert(head == tmp);
    tmp = read_node(b, 2);
    head = push_end(head, tmp);
    // ck_assert(head->next == tmp);
    tmp = read_node(b, 3);
    head = push_end(head, tmp);
    // ck_assert(head->next == tmp);
    
    ck_assert_list_array_eq(head, b, 3);
    // size_t i = 0;
    // tmp = head;
    // while (tmp)
    // {
    //     ck_assert_int_eq(*(int *) tmp->data, b[i]);
    //     tmp = tmp->next;
    //     i++;
    // }
    // ck_assert_int_eq(i, 3); //Размер 4
    list_free(head);
}
END_TEST

///Попробуем 2 раза удалить узлы из начала
START_TEST(PopFront)
{
    node_t *head = NULL;
    int b[2] = { 1, 2 };

    void *data = pop_front(&head);
    ck_assert_ptr_null(data);
    
    head = create_list(b, 2);
    // node_t *tmp = read_node(b, 2);
    // head = push_front(head, tmp);
    // tmp = read_node(b, 1);
    // head = push_front(head, tmp);

    data = pop_front(&head);
    ck_assert_int_eq(*(int *) data, 1);
    data = pop_front(&head);
    ck_assert_int_eq(*(int *) data, 2);
    data = pop_front(&head);
    ck_assert_ptr_null(data);
    data = pop_front(&head);
    ck_assert_ptr_null(data);
    data = pop_front(&head);
    ck_assert_ptr_null(data);
    data = pop_front(&head);
    ck_assert_ptr_null(data);
    
    head = push_front(head, read_node(b, 1));
    data = pop_front(&head);
    ck_assert_int_eq(*(int *) data, 1);
    data = pop_front(NULL);
    // list_free(head);
}
END_TEST

///Попробуем два раза удалить с конца узлы
START_TEST(PopEnd)
{
    node_t *head = NULL;
    int b[2] = { 1, 2 };
    void *data = NULL;

    data = pop_back(&head);
    ck_assert_ptr_null(data);
    
    head = create_list(b, 2);
    // node_t *tmp = read_node(b, 2);
    // head = push_front(head, tmp);
    // tmp = read_node(b, 1);
    // head = push_front(head, tmp);

    data = pop_back(&head);
    ck_assert_int_eq(*(int *) data, 2);
    data = pop_back(&head);
    ck_assert_int_eq(*(int *) data, 1);
    data = pop_back(&head);
    ck_assert_ptr_null(data);

    // list_free(head);
}
END_TEST

///Вставка элемента по середине
START_TEST(Insert1)
{
    node_t *head = NULL;
    int b[3] = { 1, 2, 3 };

    node_t *tmp = read_node(b, 3);
    head = push_front(head, tmp);
    tmp = read_node(b, 1);
    head = push_front(head, tmp);
    
    assert(head);
    tmp = read_node(b, 2);
    insert(&head, tmp, head->next);
    ck_assert(head->next == tmp);
    
    ck_assert_list_array_eq(head, b, 3);
    list_free(head);
}
END_TEST

///Вставка элемента перед головой
START_TEST(Insert2)
{
    node_t *head = NULL;
    int b[3] = { 1, 2, 3 };

    node_t *tmp = read_node(b, 3);
    head = push_front(head, tmp);
    tmp = read_node(b, 2);
    head = push_front(head, tmp);
    
    assert(head);
    tmp = read_node(b, 1);
    insert(&head, tmp, head);
    ck_assert(head == tmp);
    
    ck_assert_list_array_eq(head, b, 3);

    list_free(head);
}
END_TEST

///Вставка элемента перед концом
START_TEST(Insert3)
{
    node_t *head = NULL;
    int b[4] = { 1, 2, 3, 4 };

    node_t *tmp = read_node(b, 4);
    node_t *before = tmp; //Узел со значением 4
    head = push_front(head, tmp);
    tmp = read_node(b, 2);
    head = push_front(head, tmp);
    tmp = read_node(b, 1);
    head = push_front(head, tmp);
    
    assert(head);
    tmp = read_node(b, 3);
    insert(&head, tmp, before);
    
    ck_assert_list_array_eq(head, b, 4);

    list_free(head);
}
END_TEST

///Вставка элемента в спмсок, где 1 элемент
START_TEST(Insert4)
{
    node_t *head = NULL;
    int b[2] = { 1, 2 };

    node_t *tmp = read_node(b, 2);
    node_t *before = tmp; //Узел со значением 2
    head = push_front(head, tmp);
    
    assert(head);
    tmp = read_node(b, 1);
    insert(&head, tmp, before);
    
    ck_assert_list_array_eq(head, b, 2);

    list_free(head);
}
END_TEST

///Вставка элемента в конец списка
START_TEST(Insert5)
{
    node_t *head = NULL;
    int b[2] = { 1, 2 };

    node_t *tmp = read_node(b, 1);
    node_t *before = NULL; //Конец списка
    head = push_front(head, tmp);
    
    assert(head);
    tmp = read_node(b, 2);
    insert(&head, tmp, before);
    
    ck_assert_list_array_eq(head, b, 2);

    list_free(head);
}
END_TEST

///Вставка элемента, которого нет в списке
START_TEST(Insert6)
{
    node_t *head = NULL;
    int b[2] = { 1, 2 };

    int a = 1;
    node_t *tmp = read_node(b, 1);
    node_t *before = node_create(&a); //Такого нет узла в списке
    head = push_front(head, tmp);

    assert(head);
    node_t *tmp2 = read_node(b, 2);
    insert(&head, tmp2, before);
    
    //Razmer odin, potomu chto my ne vstavili element v spisok
    ck_assert_list_array_eq(head, b, 1);

    list_free(head);
    node_free(before);
    node_free(tmp2);
}
END_TEST

///Оба списка наполнены узлами
START_TEST(Append1)
{
    node_t *head_a = NULL, *head_b = NULL;
    int b[4] = { 1, 2, 3, 4 };
    
    head_a = create_list(b, 2);
    
    head_b = create_list(b + 2, 2);

    append(&head_a, &head_b);
    ck_assert_ptr_null(head_b);
    //list: 1->2->3->4

    ck_assert_list_array_eq(head_a, b, 4);
    list_free(head_a);
}
END_TEST

///Список А пуст
START_TEST(Append2)
{
    node_t *head_a = NULL, *head_b = NULL;
    int b[2] = { 1, 2 };
    
    head_a = create_list(b, 2);

    append(&head_a, &head_b);
    ck_assert_ptr_null(head_b);
    //list: 1->2
    
    ck_assert_list_array_eq(head_a, b, 2);

    list_free(head_a);
}
END_TEST

///Список Б пуст
START_TEST(Append3)
{
    node_t *head_a = NULL, *head_b = NULL;
    int b[2] = { 1, 2 };
    
    head_b = create_list(b, 2);
    // node_t *tmp = read_node(b, 2);
    // head_a = push_front(head_a, tmp);
    // tmp = read_node(b, 1);
    // head_a = push_front(head_a, tmp);

    append(&head_a, &head_b);
    ck_assert_ptr_null(head_b);
    //list: 1->2
    
    ck_assert_list_array_eq(head_a, b, 2);

    list_free(head_a);
}
END_TEST

//Сортировка одного элемента
START_TEST(Sort1)
{
    int b[1]= { 1 };

    node_t *head = read_node(b, 1);

    head = sort(head, intcmp);
    
    ck_assert_list_array_eq(head, b, sizeof(b) / sizeof(*b));
    // node_t *tmp = head;
    // size_t i = 0;
    // while (tmp)
    // {
    //     ck_assert_int_eq(*(int *) tmp->data, b[i]);
    //     i++;
    //     tmp = tmp->next;
    // }
    // ck_assert_uint_eq(i, sizeof(b) / sizeof(*b));

    list_free(head);
}
END_TEST

//Сортировка двух упорядоченных элементов
START_TEST(Sort2)
{
    int b[2]= { 1, 2 };

    // node_t *head = read_node(b, 1);
    // head = push_end(head, read_node(b, 2));
    
    node_t *head = create_list(b, 2);
    head = sort(head, intcmp);
    
    ck_assert_list_array_eq(head, b, sizeof(b) / sizeof(*b));

    list_free(head);
}
END_TEST

//Сортировка двух упорядоченных в обратном порядке элементов
START_TEST(Sort3)
{
    int b[2]= { 1, 2 };

    node_t *head = read_node(b, 2);
    head = push_end(head, read_node(b, 1));

    head = sort(head, intcmp);
    
    ck_assert_list_array_eq(head, b, sizeof(b) / sizeof(*b));

    list_free(head);
}
END_TEST

//Сортировка множества упорядоченных элементов
START_TEST(Sort4)
{
    int b[4]= { 1, 2, 3, 4 };

    node_t *head = read_node(b, 1);
    head = push_end(head, read_node(b, 2));
    head = push_end(head, read_node(b, 3));
    head = push_end(head, read_node(b, 4));

    head = sort(head, intcmp);
    
    ck_assert_list_array_eq(head, b, sizeof(b) / sizeof(*b));

    list_free(head);
}
END_TEST

//Сортировка множества упорядоченных в обратном порядке элементов
START_TEST(Sort5)
{
    int b[4]= { 1, 2, 3, 4 };

    node_t *head = read_node(b, 4);
    head = push_end(head, read_node(b, 3));
    head = push_end(head, read_node(b, 2));
    head = push_end(head, read_node(b, 1));

    head = sort(head, intcmp);
    
    ck_assert_list_array_eq(head, b, sizeof(b) / sizeof(*b));

    list_free(head);
}
END_TEST

//Сортировка множества несортированных эл-ов
START_TEST(Sort6)
{
    int b[5]= { 1, 2, 3, 4, 5 };

    node_t *head = read_node(b, 4);
    head = push_end(head, read_node(b, 2));
    head = push_end(head, read_node(b, 5));
    head = push_end(head, read_node(b, 1));
    head = push_end(head, read_node(b, 3));

    head = sort(head, intcmp);
    
    ck_assert_list_array_eq(head, b, sizeof(b) / sizeof(*b));

    list_free(head);
}
END_TEST

//Сортировка множества несортированных эл-ов с повторениями
START_TEST(Sort7)
{
    int b[10]= { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };

    node_t *head = read_node(b, 2);
    head = push_end(head, read_node(b, 3));
    head = push_end(head, read_node(b, 10));
    head = push_end(head, read_node(b, 4));
    head = push_end(head, read_node(b, 6));
    head = push_end(head, read_node(b, 5));
    head = push_end(head, read_node(b, 7));
    head = push_end(head, read_node(b, 1));
    head = push_end(head, read_node(b, 9));
    head = push_end(head, read_node(b, 8));

    head = sort(head, intcmp);
    
    ck_assert_list_array_eq(head, b, sizeof(b) / sizeof(*b));

    list_free(head);
}
END_TEST

//Четное количество узлов
START_TEST(frontbacksplit1)
{
    
    int b[10]= { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };

    node_t *head = read_node(b, 1);
    head = push_end(head, read_node(b, 2));
    head = push_end(head, read_node(b, 3));
    head = push_end(head, read_node(b, 4));
    //1->1->2->2

    node_t *back = NULL;
    front_back_split(head, &back);
    ck_assert(head && back);

    size_t i = 0;
    node_t *tmp = head;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 1);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 2);
    i = 0;
    tmp = back;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 2);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 2);

    list_free(head);
    list_free(back);
}
END_TEST

//Нечетное количество узлов
START_TEST(frontbacksplit2)
{
    
    int b[10]= { 1, 1, 1, 2, 2, 3, 4, 4, 5, 5 };

    node_t *head = read_node(b, 1);
    head = push_end(head, read_node(b, 2));
    head = push_end(head, read_node(b, 3));
    head = push_end(head, read_node(b, 4));
    head = push_end(head, read_node(b, 5));
    //1->1->1->2->2

    node_t *back = NULL;
    front_back_split(head, &back);
    ck_assert(head && back);

    size_t i = 0;
    node_t *tmp = head;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 1);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 3);
    i = 0;
    tmp = back;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 2);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 2);

    list_free(head);
    list_free(back);
}
END_TEST

//1 узел
START_TEST(frontbacksplit3)
{
    
    int b[10]= { 1, 1, 1, 2, 2, 3, 4, 4, 5, 5 };

    node_t *head = read_node(b, 1);
    //1

    node_t *back = NULL;
    front_back_split(head, &back);
    ck_assert(head && !back);

    size_t i = 0;
    node_t *tmp = head;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 1);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 1);
    i = 0;
    tmp = back;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 2);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 0);

    list_free(head);
    list_free(back);
}
END_TEST

//2 узла
START_TEST(frontbacksplit4)
{
    
    int b[10]= { 1, 2, 1, 2, 2, 3, 4, 4, 5, 5 };

    node_t *head = read_node(b, 1);
    head = push_end(head, read_node(b, 2));
    //1->2

    node_t *back = NULL;
    front_back_split(head, &back);
    ck_assert(head && back);

    size_t i = 0;
    node_t *tmp = head;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 1);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 1);
    i = 0;
    tmp = back;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 2);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 1);

    list_free(head);
    list_free(back);
}
END_TEST

//0 узлов
START_TEST(frontbacksplit5)
{
    
    node_t *head = NULL;
    node_t *back = NULL;
    front_back_split(head, &back);
    ck_assert(!head && !back);

    size_t i = 0;
    node_t *tmp = head;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 1);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 0);
    i = 0;
    tmp = back;
    while (tmp)
    {
        ck_assert_int_eq(*(int *) tmp->data, 2);
        i++;
        tmp = tmp->next;
    }
    ck_assert_uint_eq(i, 0);

    list_free(head);
    list_free(back);
}
END_TEST

//Vse podspiski odinakovoy dliny
START_TEST(SortedMerge1)
{
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    node_t *a = read_node(b, 1);
    a = push_end(a, read_node(b, 2));
    a = push_end(a, read_node(b, 3));
    a = push_end(a, read_node(b, 4));
    a = push_end(a, read_node(b, 5));

    node_t *f = read_node(b, 6);
    f = push_end(f, read_node(b, 7));
    f = push_end(f, read_node(b, 8));
    f = push_end(f, read_node(b, 9));
    f = push_end(f, read_node(b, 10));

    node_t *c = sorted_merge(&a, &f, intcmp);

    ck_assert_ptr_null(a);
    ck_assert_ptr_null(f);
    ck_assert_list_array_eq(c, b, sizeof(b) / sizeof(*b));

    list_free(c);
}
END_TEST

//leviy podspisok bolshe vtorogo
START_TEST(SortedMerge2)
{
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    node_t *a = read_node(b, 1);
    a = push_end(a, read_node(b, 2));
    a = push_end(a, read_node(b, 3));
    a = push_end(a, read_node(b, 4));
    a = push_end(a, read_node(b, 5));
    a = push_end(a, read_node(b, 6));

    node_t *f = read_node(b, 7);
    f = push_end(f, read_node(b, 8));
    f = push_end(f, read_node(b, 9));
    f = push_end(f, read_node(b, 10));

    node_t *c = sorted_merge(&a, &f, intcmp);

    ck_assert_ptr_null(a);
    ck_assert_ptr_null(f);
    ck_assert_list_array_eq(c, b, sizeof(b) / sizeof(*b));

    list_free(c);
}
END_TEST

//Praviy podspisok bolshe levogo
START_TEST(SortedMerge3)
{
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    node_t *a = read_node(b, 1);
    a = push_end(a, read_node(b, 2));
    a = push_end(a, read_node(b, 3));
    a = push_end(a, read_node(b, 4));

    node_t *f = read_node(b, 5);
    f = push_end(f, read_node(b, 6));
    f = push_end(f, read_node(b, 7));
    f = push_end(f, read_node(b, 8));
    f = push_end(f, read_node(b, 9));
    f = push_end(f, read_node(b, 10));

    node_t *c = sorted_merge(&a, &f, intcmp);

    ck_assert_list_array_eq(c, b, sizeof(b) / sizeof(*b));

    list_free(c);
}
END_TEST

//Podspiski otsortirovani, odnako ih ob'edinenie netrivialno
START_TEST(SortedMerge4)
{
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    node_t *a = read_node(b, 1);
    a = push_end(a, read_node(b, 3));
    a = push_end(a, read_node(b, 5));
    a = push_end(a, read_node(b, 7));
    a = push_end(a, read_node(b, 9));

    node_t *f = read_node(b, 2);
    f = push_end(f, read_node(b, 4));
    f = push_end(f, read_node(b, 6));
    f = push_end(f, read_node(b, 8));
    f = push_end(f, read_node(b, 10));

    node_t *c = sorted_merge(&a, &f, intcmp);

    ck_assert_ptr_null(a);
    ck_assert_ptr_null(f);
    ck_assert_list_array_eq(c, b, sizeof(b) / sizeof(*b));

    list_free(c);
}
END_TEST

//Podspiski iz 1 elementa
START_TEST(SortedMerge5)
{
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    node_t *a = read_node(b, 1);

    node_t *f = read_node(b, 2);

    node_t *c = sorted_merge(&a, &f, intcmp);

    ck_assert_ptr_null(a);
    ck_assert_ptr_null(f);
    ck_assert_list_array_eq(c, b, 2);

    list_free(c);
}
END_TEST

//Podspiski leviy podspisok pustoi
START_TEST(SortedMerge6)
{
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    node_t *a = NULL;

    node_t *f = read_node(b, 1);

    node_t *c = sorted_merge(&a, &f, intcmp);

    ck_assert_ptr_null(a);
    ck_assert_ptr_null(f);
    ck_assert_list_array_eq(c, b, 1);

    list_free(c);
}
END_TEST

//Podspiski praviy podspisok pustoi
START_TEST(SortedMerge7)
{
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    node_t *a = read_node(b, 1);

    node_t *f = NULL;

    node_t *c = sorted_merge(&a, &f, intcmp);

    ck_assert_ptr_null(a);
    ck_assert_ptr_null(f);
    ck_assert_list_array_eq(c, b, 1);

    list_free(c);
}
END_TEST

Suite *get_list_suite(void)
{
    Suite *suite = suite_create("List test");

    TCase *oper = tcase_create("Operations");
    tcase_add_test(oper, PushFront);
    tcase_add_test(oper, PushEnd);
    tcase_add_test(oper, PopFront);
    tcase_add_test(oper, PopEnd);
    tcase_add_test(oper, Insert1);
    tcase_add_test(oper, Insert2);
    tcase_add_test(oper, Insert3);
    tcase_add_test(oper, Insert4);
    tcase_add_test(oper, Insert5);
    tcase_add_test(oper, Insert6);
    tcase_add_test(oper, Append1);
    tcase_add_test(oper, Append2);
    tcase_add_test(oper, Append3);
    tcase_add_test(oper, frontbacksplit1);
    tcase_add_test(oper, frontbacksplit2);
    tcase_add_test(oper, frontbacksplit3);
    tcase_add_test(oper, frontbacksplit4);
    tcase_add_test(oper, frontbacksplit5);
    tcase_add_test(oper, SortedMerge1);
    tcase_add_test(oper, SortedMerge2);
    tcase_add_test(oper, SortedMerge3);
    tcase_add_test(oper, SortedMerge4);
    tcase_add_test(oper, SortedMerge5);
    tcase_add_test(oper, SortedMerge6);
    tcase_add_test(oper, SortedMerge7);

    TCase *sort = tcase_create("Sorts");
    tcase_add_test(sort, Sort1);
    tcase_add_test(sort, Sort2);
    tcase_add_test(sort, Sort3);
    tcase_add_test(sort, Sort4);
    tcase_add_test(sort, Sort5);
    tcase_add_test(sort, Sort6);
    tcase_add_test(sort, Sort7);

    suite_add_tcase(suite, oper);
    suite_add_tcase(suite, sort);

    return suite;
}

