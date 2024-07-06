#include "logic.h"

int parse_string(char *string, char result[][MAX_WORD_SIZE], size_t *count)
{
    *count = 0;
    char *word = strtok(string, DELIM);

    while (word != NULL)
    {
        if (*count < MAX_STRLEN / 2)
        {
            strncpy(result[(*count)++], word, MAX_WORD_SIZE);
            word = strtok(NULL, DELIM);
        }
        else
        {
            return ERR_TOO_MANY_WORDS;
        }
    }

    return OK;
}

// char *get_next_word(void)
// {
//     return strtok(NULL, DELIM);
// }

// int copy_word(char *pbegin, const char *pend, char *word, size_t word_size)
// {
//     if ((size_t) (pend - pbegin + 1) > word_size)
//         return ERR_BUF_TOO_SMALL;

//     size_t index = 0;
//     char *pcurrent = pbegin;
//     while (pcurrent < pend)
//     {
//         word[index++] = *pcurrent;
//         pcurrent++;
//     }
//     word[index] = 0;
//     return OK;
// }


// int parse_string(char *string, char result[][MAX_WORD_SIZE], size_t *size)
// {
//     char *pbegin, *pend, *pcurrent = string;
//     size_t n = 0;
//     int return_code = OK;
//     bool first = true;

//     while (!return_code && pcurrent && *pcurrent)
//     {
//         // get_next_word(pcurrent, &pbegin, &pend);
//         if (first)
//         {
//             pcurrent = strtok(string, DELIM);
//             first = false;
//         }
//         else
//         {
//             pcurrent = get_next_word();
//         }

//         if (pbegin)
//         {
//             if (n < MAX_STRLEN / 2)
//             {
//                 return_code = copy_word(pbegin, pend, result[n], sizeof(result[n]));
//                 if (return_code == 0)
//                     n++;
//             }
//             else
//                 return_code = ERR_TOO_MANY_WORDS;
//         }
//         pcurrent = pend;
//     }

//     if (n == 0)
//         return return_code;

//     if (return_code == OK)
//         *size = n;

//     return return_code;
// }

// int left_only_uniq_chars(char *string)
// {
//     char temp_string[MAX_WORD_SIZE] = { string[0], '\0' };
//     size_t string_lenght = strlen(string), size_temp = 1;
//     bool is_uniq;

//     for (size_t i = 1; i < string_lenght; i++)
//     {
//         is_uniq = true;
//         for (size_t j = 0; j < size_temp && is_uniq; j++)
//         {
//             if (string[i] == temp_string[j])
//             {
//                 is_uniq = false;
//             }
//         }
//         if (is_uniq)
//             temp_string[size_temp++] = string[i];
//     }
//     if (size_temp == 0)
//         return ERR_IO;
//     strcpy(string, temp_string);
//     return OK;
// }

bool is_char_uniq(char *pbeg, char *pend, char ch)
{
    size_t count = 0;
    for (char *pcur = pbeg; pcur < pend && count < 2; pcur++)
    {
        if (*pcur == ch)
        {
            count++;
        }
    }
    if (count == 1)
        return true;
    return false;
}

int left_only_uniq_chars(char *string)
{
    size_t size = 0;
    for (size_t i = 0; string[i] != '\0'; i++)
    {
        if (is_char_uniq(string, string + i + 1, string[i]))
        {
            string[size++] = string[i];
        }
    }
    if (size == 0)
        return ERR_IO;
    string[size] = 0;
    return OK;
}

// int left_only_uniq_chars(char *string)
// {
    
//     if (strlen(string) == 0)
//         return ERR_IO;
//     return OK;
// }

int form_string(char words[][MAX_WORD_SIZE], size_t word_count, char buffer[], size_t buffer_size)
{
    size_t need = 0;
    char *lastword;
    lastword = words[word_count - 1];

    // for (size_t i = 0; i < word_count - 1; i++)
    if (word_count < 2)
        return ERR_IO;
    for (size_t i = 0; i < word_count - 2; i++)
    {
        need = need + (strlen(words[i]) + 1);
        if (need > buffer_size)
            return ERR_BUF_TOO_SMALL;
    }
    buffer[0] = 0;
    if (word_count < 2)
        return ERR_IO;
    
    for (size_t i = word_count - 2; i > 0; i--)
    {
        if (left_only_uniq_chars(words[i]) != OK)
            return ERR_IO;
        if (strcmp(words[i], lastword) != 0)
        {
            strcat(buffer, words[i]);
            strcat(buffer, " ");
        }
    }
    if (left_only_uniq_chars(words[0]) != OK)
        return ERR_IO;
    if (strcmp(words[0], lastword) != 0)
        strcat(buffer, words[0]);
    return OK;
}
