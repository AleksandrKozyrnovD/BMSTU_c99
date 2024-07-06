#include "sort.h"
#include "fileread.h"
#include <assert.h>
#include <string.h>

/**
 * @brief Функция для смены двух элементов местами
 *
 * @param[in,out] l Указатель на левый элемент
 * @param[in,out] r Указатель на правый элемент
 * @param[in] nmem Размер этих двух элементов
 */
static void swap(void *l, void *r, size_t nmem)
{
    char tmp;
    char *pl = l, *pr = r;
    for (size_t i = 0; i < nmem; i++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
        pl++;
        pr++;
    }
}

/**
 * @brief Функция бинарного поиска
 *
 * @param[in] base Указатель на начало массива 
 * @param[in] data Указатель на элемент массива, который ищем
 * @param[in] nmemb Кол-во элементов массива
 * @param[in] size Размер элемента
 * @param[in] cmp Указатель на функцию сравнителя
 * @return Индекс в массиве
 */
// static size_t binary_search(const void *base, const void *data, size_t nmemb, size_t size, comparator_t cmp)
// {
//     assert((nmemb > 0));
//     int left = 0;
//     int right = nmemb - 1;
//     int mid;
//     void *middle;
//     int cmp_score;
//
//     while (left <= right)
//     {
//         mid = left + ((right - left) / 2);
//         middle = (char *) base + (mid * size);
//         
//         cmp_score = cmp(data, middle);
//
//         if (cmp_score == 0)
//             return mid;
//         else if (cmp_score < 0)
//             right = mid - 1;
//         else
//             left = mid + 1;
//     }
//
//     return left;
// }

/**
 * @brief Функция бинарного поиска элемента в массиве
 *
 * @param[in] base Указатель на начало массива
 * @param[in] end Указатель на законец массива
 * @param[in] data Искомый элемент
 * @param[in] size Размер элементов
 * @param[in] cmp Указатель на функцию сравнитель
 * @return Указатель на область, где он должен лежать
 */
static void *binary_search(const void *base, const void *end, const void *data, size_t size, comparator_t cmp)
{
    const char *left = base;
    const char *right = end;
    if (left > right)
        return (void *) (left);

    const char *mid;
    int cmp_score;
    while (left <= right)
    {
        /*
         * Аналог выражения для индексов: mid = left + (right - left) / 2   (1)
         *                                mid = (right + left) / 2          (2)
         *
         * Его результатом является (1/2 * left) + (1/2 * right), то есть тоже самое, что и (right + left) / 2
         *
         * Однако при использовании указателей для выражения (2) их нельзя сложить (по причине, что это бессмысленно - складывать 2 адреса).
         * Но можно использовать свойства адресной арифметики:
         * 1) При разности двух указателей возвращается ptr_diff_t, что в свою очередь уже число, а не адрес
         * 2) Сложение адреса и числа дает новый адрес (смещенный относительно старого)
         * Из этого следует, что единственный вариант - это выражение (1)
         *
         * Рассмотрение причин деления и умножения на size и почему по-другому нельзя.
         * По условию мы не знаем заранее тип элемента, отчего переводим указатель на пустоту в указатель на символ.
         * Условимся на том, что разница между двумя такими равна кол-ву байтов между ними. То есть если не делить на размер типа,
         * мы можем получить "промежуточный адрес". Например,
         * если у нас два соседних числа размером 4, их адреса 100 и 104 соответственно, то данное выражение выдало бы адрес 102.
         * Это не адрес элемента, а адрес между ними. При делении разницы (104 - 100) = 4 на размер (4 байта), получаем сколько элементов
         * действительно между ними - 4 / 4 = 1. Теперь эту разницу следует разделить на 2 (как и в оригинальном выражении).
         * Но если прекратить действия и не умножать на размер типа, то мы получим только количество элементов, на которое следует перейти от левого
         * края. Чтобы перевести количество элементов в количество байт, требуемого для перемещения указателя, мы домножаем
         * результат на размер типа.
         *
         * Почему это нельзя сократить (вообще не использовать size)? Потому что это следовало бы записать это как алгоритм с такими действиями:
         * 1) Найти разницу в адресах
         * 2) Понять, сколько в этой разнице может храниться элементов (например, от 100 до 116 может храниться 4 целых числа). Тут происходит деление
         *    на размер типа
         * 3) Найти средний между ними. Тут происходит деление на 2
         * 4) Перевести количество элементов обратно в разницу байт. Тут происходит умножение на размер типа.
         *
         * То есть при сокращении умножения/деления на size (размер типа), мы теряем пункты 2) и 4) соответственно.
         *
         * Этого можно было избежать, если мы заранее смогли знать тип элементов.
         * */
        mid = (left + ((right - left) / size) / 2 * size);

        cmp_score = cmp(data, mid);
        if (cmp_score == 0)
            return (void *) mid;
        else if (cmp_score < 0)
            right = mid - size;
        else if (cmp_score > 0)
        {
            left = mid + size;
        }
    }

    return (void *) (left);
}
// static void *binary_search(const void *base, const void *end, const void *data, size_t size, comparator_t cmp)
// {
//     const char *left = base;
//     const char *right = end;
//     if (left > right)
//         return (void *) (left);
//
//     const char *mid;
//     int cmp_score;
//
//     mid = (left + ((right - left) / size) / 2 * size);
//
//     cmp_score = cmp(data, mid);
//
//     if (cmp_score == 0)
//         return (void *) mid;
//     else if (cmp_score < 0)
//         return binary_search(base, mid - size, data, size, cmp);
//     else
//         return binary_search(left + size, right, data, size, cmp);
// }

/**
 * @brief Функция вставки элемента в массив
 *
 * @param[in,out] base Указательна массив
 * @param[in] nmemb Кол-во элементов
 * @param[in] size Размкр элемента
 * @param[in] pos Позиция вставки
 */
// static void insert(void *base, size_t nmemb, size_t size, size_t pos)
// {
//     char *arr = (char*) base;
//     for (size_t i = nmemb; i >= pos + 1; i--)
//         swap(arr + i * size, arr + (i - 1) * size, size);
// }

static void insert_swap(void *start, void *end, size_t size)
{
    char *index = start;
    char *from = end;
    for (char *pcur = from; pcur > index; pcur -= size)
        swap(pcur, pcur - size, size);
}

// static void insert(void *base, void *end, const void *data, size_t size)
// {
//     char *pos = base;
//     char *pend = end;
//
//     for (char *pcur = pend; pcur > pos; pcur -= size)
//     {
//         memcpy(pcur, pcur - size, size);
//     }
//     memcpy(pos, data, size);
// }

void mysort(void *base, size_t nmemb, size_t size, comparator_t cmp)
{
    if (!size)
        return;

    // size_t index;
    
    // for (size_t i = 1; i < nmemb; ++i)
    // {
    //     void *curr = (char *) base + i * size;
    //     index = binary_search(base, curr, i, size, cmp);
    //     insert(base, i, size, index);
    // }

    // char tmp[size]; //VLA
    // char *pbeg = base;
    // char *pend = pbeg + nmemb * size;
    // char *index;
    // 
    // for (char *pcur = pbeg + size; pcur < pend; pcur += size)
    // {
    //     memcpy(tmp, pcur, size);
    //     index = binary_search(base, pcur - size, pcur, size, cmp);
    //     memmove(index + size, index, pcur - index);
    //     memcpy(index, tmp, size);
    //     // insert(index, pcur, tmp, size);
    // }

    // char tmp[size]; //VLA
    char *pbeg = base;
    char *pend = pbeg + nmemb * size;
    char *index;
    
    for (char *pcur = pbeg + size; pcur < pend; pcur += size)
    {
        // memcpy(tmp, pcur, size);
        index = binary_search(base, pcur - size, pcur, size, cmp);
        insert_swap(index, pcur, size);
        // memmove(index + size, index, pcur - index);
        // memcpy(index, tmp, size);
        // insert(index, pcur, tmp, size);
    }
}

