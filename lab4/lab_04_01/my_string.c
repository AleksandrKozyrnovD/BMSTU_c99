#include <stdbool.h>
#include "my_string.h"
#include "includes.h"


bool have_char(const char *str, char ch)
{
    size_t index = 0;

    if (ch == '\0')
        return false;

    while (str[index] != '\0')
    {
        if (str[index] == ch)
            return true;
        index++;
    }
    
    return false;
}

char *my_strpbkr(const char *string1, const char *string2)
{
    // for (size_t i = 0; string1[i] != '\0'; i++)
    for (size_t i = 0; have_char(string1, string1[i]); i++)
    {
        // for (size_t j = 0; string2[j] != '\0'; j++)
        for (size_t j = 0; have_char(string2, string2[j]); j++)
        {
            if (string1[i] == string2[j])
            {
                // return &string1[i];
                return ((char *) (string1 + i));
            }
        }
    }
    return NULL;
}


size_t my_strspn(const char *string1, const char *string2)
{
    size_t count = 0;

    // for (size_t i = 0; string1[i] != '\0'; i++)
    for (size_t i = 0; have_char(string1, string1[i]); i++)
    {
        size_t index = 0;
        // for (size_t j = 0; string2[j] != '\0' && string1[i] != string2[j]; j++)
        for (size_t j = 0; have_char(string2, string2[j]) && string1[i] != string2[j]; j++)
            index++;

        if (string1[i] != string2[index])
            return count;
        
        count++;
    }
    return count;
}


size_t my_strcspn(const char *string1, const char *string2)
{
    size_t count = 0;

    // for (size_t i = 0; string1[i] != '\0'; i++)
    for (size_t i = 0; have_char(string1, string1[i]); i++)
    {
        size_t index = 0;
        // for (size_t j = 0; string2[j] != '\0' && string1[i] != string2[j]; j++)
        for (size_t j = 0; have_char(string2, string2[j]) && string1[i] != string2[j]; j++)
            index++;

        if (string1[i] == string2[index])
            return count;
        
        count++;
    }
    return count;
}


char *my_strchr(const char *string1, const char ch)
{
    size_t index = 0;
    // while (string1[index] != '\0')
    while (have_char(string1, string1[index]))
    {
        if (string1[index] == ch)
            return ((char *) (string1 + index));
            // return &string1[index];
        index++;
    }

    if (ch == '\0')
        return ((char *) (string1 + index));
        // return &string1[index];
    
    return NULL;
}

char *my_strrchr(const char *string1, const char ch)
{
    size_t index = 0;
    char *result = NULL;

    // while (string1[index] != '\0')
    while (have_char(string1, string1[index]))
    {
        if (string1[index] == ch)
            result = ((char *) (string1 + index));
            // result = &string1[index];
        index++;
    }

    if (ch == '\0')
        result = ((char *) (string1 + index));
        // result = &string1[index];
    return result;
}
