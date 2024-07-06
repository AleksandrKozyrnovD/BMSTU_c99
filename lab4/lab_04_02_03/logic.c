#include "logic.h"


void get_next_word(char *string, char **pbegin, char **pend)
{
    char *pcurrent = string;
    *pbegin = *pend = NULL;

    while (*pcurrent && strchr(DELIM, *pcurrent))
    {
        pcurrent++;
    }
    if (!(*pcurrent))
        return;
    
    *pbegin = pcurrent;
    while (*pcurrent && !strchr(DELIM, *pcurrent))
        pcurrent++;
    *pend = pcurrent;
}

int copy_word(char *pbegin, char *pend, char *word, size_t word_size)
{
    if ((size_t) (pend - pbegin + 1) > word_size)
        return ERR_BUF_TOO_SMALL;

    size_t index = 0;
    char *pcurrent = pbegin;
    while (pcurrent < pend)
    {
        word[index++] = *pcurrent;
        pcurrent++;
    }
    word[index] = 0;
    return OK;
}

int parse_string(char *string, char result[][MAX_WORD_SIZE], size_t *size)
{
    char *pbegin, *pend, *pcurrent = string;
    size_t n = 0;
    int return_code = OK;

    while (!return_code && pcurrent && *pcurrent)
    {
        get_next_word(pcurrent, &pbegin, &pend);
        if (pbegin)
        {
            if (n < MAX_COUNT_WORDS)
            {
                return_code = copy_word(pbegin, pend, result[n], sizeof(result[n]));
                if (return_code == 0)
                    n++;
            }
            else
                return_code = ERR_TOO_MANY_WORDS;
        }
        pcurrent = pend;
    }

    if (n == 0)
        return return_code;

    if (return_code == OK)
        *size = n;

    return return_code;
}

// bool is_uniq(char array_words1[][MAX_WORD_SIZE], size_t size1, char array_words2[][MAX_WORD_SIZE], size_t size2, const char word[MAX_WORD_SIZE], size_t word_index)
// {
//     for (size_t i = 0; i < size1; i++)
//     {
//         if (i != word_index)
//         {
//             if (strcmp(array_words1[i], word) == 0)
//                 return false;
//         }
//     }

//     for (size_t i = 0; i < size2; i++)
//     {
//         if (strcmp(array_words2[i], word) == 0)
//             return false;
//     }

//     return true;
// }

// bool is_uniq(char array_words[][MAX_WORD_SIZE], size_t size, const char word[MAX_WORD_SIZE])
// {
//     size_t count = 0;
//     for (size_t i = 0; i < size && count < 2; i++)
//     {
//         if (strcmp(array_words[i], word) == 0)
//         {
//             count++;
//         }
//     }
//     if (count == 1)   
//         return true;
// }

// int form_uniq_array(char words[][MAX_STRLEN], size_t size1, char uniq[][MAX_STRLEN], size_t *size2)
// {
//     bool is_empty = true;
//     for (size_t i = 0; i < size1; i++)
//     {
//         if (is_uniq(words, size1, words[i]))
//         {
//             strcpy(uniq[(*size2)++], words[i]);
//             is_empty = false;
//         }
//     }

//     if (is_empty)
//         return 1; //empty
    
//     return 0; //full
// }
