#include "inputoutput.h"

int get_line(char *buf, size_t buf_size)
{
    char *ptr;
    // printf("Input string: ");
    if (!fgets(buf, buf_size, stdin))
        return ERR_IO;
    if ((strlen(buf) == MAX_STRLEN) && (buf[strlen(buf) - 1] != '\n'))
        return ERR_BUF_TOO_SMALL;
        
    ptr = strrchr(buf, '\n');
    if (ptr)
    {
        *ptr = 0;
        return OK;
    }
    return ERR_BUF_TOO_SMALL;
}

// int print_uniq(char words1[][MAX_WORD_SIZE], size_t size1, char words2[][MAX_WORD_SIZE], size_t size2)
// {
//     bool is_empty = true;
//     bool first = true;
//     // printf("Result: ");
//     for (size_t i = 0; i < size1; i++)
//     {
//         if (is_uniq(words1, size1, words2, size2, words1[i], i))
//         {
//             if (first)
//             {
//                 printf("Result: ");
//                 first = false;
//             }
//             printf("%s ", words1[i]);
//             is_empty = false;
//         }
//     }

//     for (size_t i = 0; i < size2; i++)
//     {
//         if (is_uniq(words2, size2, words1, size1, words2[i], i))
//         {
//             if (first)
//             {
//                 printf("Result: ");
//                 first = false;
//             }
//             printf("%s ", words2[i]);
//             is_empty = false;
//         }
//     }
//     if (is_empty)
//         return ERR_IO;
//     printf("\n");
//     return OK;
// }

/**
 * @brief Функция, которая проверяет, является ли оно уникальным
 * 
 * @param array_words Массив слов
 * @param size Размер массива
 * @param word Слово, которое проверяем на уникальность в массиве слов
 * @param mine Признак принадлежности к этому массиву (то есть если мы уверены, что он там точно есть)
 * 
 * @returns
 * Правда или ложь
*/
bool is_uniq(char array_words[][MAX_WORD_SIZE], size_t size, const char word[MAX_WORD_SIZE], bool mine)
{
    size_t count = 0;
    for (size_t i = 0; i < size && count < 2; i++)
    {
        if (strcmp(array_words[i], word) == 0)
        {
            count++;
        }
    }
    if (count == 1 && mine)   
        return true;
    else if (count == 0 && !mine)
        return true;
    return false;
}

int form_uniq_array(char words1[][MAX_WORD_SIZE], size_t size1, char words2[][MAX_WORD_SIZE], size_t size2, char uniq[][MAX_WORD_SIZE], size_t *size3)
{
    bool is_empty = true;

    //Для первого массива слов
    for (size_t i = 0; i < size1; i++)
    {
        if (is_uniq(words1, size1, words1[i], true) && is_uniq(words2, size2, words1[i], false))
        {
            is_empty = false;
            strcpy(uniq[(*size3)++], words1[i]);
        }
    }

    // for (size_t i = 0; i < size2; i++)
    // {
    //     if (is_uniq(words2, size2, words2[i], true) && is_uniq(words1, size1, words2[i], false))
    //     {
    //         is_empty = false;
    //         strcpy(uniq[(*size3)++], words2[i]);
    //     }
    // }
    if (is_empty)
        return ERR_STRING_IS_EMPTY;
    return OK;
}

int print_uniq(char words1[][MAX_WORD_SIZE], size_t size1, char words2[][MAX_WORD_SIZE], size_t size2)
{
    char uniq1[MAX_STRLEN / 2][MAX_WORD_SIZE], uniq2[MAX_STRLEN / 2][MAX_WORD_SIZE];
    size_t size_uniq1 = 0, size_uniq2 = 0;
    bool first = true;
    bool is_empty = true;

    if (form_uniq_array(words1, size1, words2, size2, uniq1, &size_uniq1) == OK)
    {
        // printf("%zu\n", size_uniq1);
        if (first)
        {
            printf("Result: ");
            first = false;
        }
        for (size_t i = 0; i < size_uniq1; i++)
        {
            printf("%s ", uniq1[i]);
            is_empty = false;
        }
    }

    if (form_uniq_array(words2, size2, words1, size1, uniq2, &size_uniq2) == OK)
    {
        if (first)
        {
            printf("Result: ");
            first = false;
        }
        for (size_t i = 0; i < size_uniq2; i++)
        {
            printf("%s ", uniq2[i]);
            is_empty = false;
        }
    }

    if (is_empty)
    {
        return ERR_STRING_IS_EMPTY;
    }
    printf("\n");
    return OK;
}
