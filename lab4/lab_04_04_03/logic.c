#include "logic.h"

/**
 * @brief Функция для проверки пробельных символов до начала номера
 * 
 * @param[in] buf Строка с номером телефона
 * @param[in] size Размер строки
 * @param[in,out] index Индекс начала строки (откуда начинаем проверять)
 * 
 * @returns
 * Правда или ложь
*/
bool correct_spacesing(const char *buf, size_t size, size_t *index)
{
    bool plus_or_border = false;

    while (!plus_or_border && *index < size)
    {
        if (buf[*index] == '+' || buf[*index] == '(')
            plus_or_border = true;
        else if (!isspace(buf[*index]))
            return false;
        (*index)++;
    }
    return plus_or_border;
}

/**
 * @brief Функция для проверки пробельных символов после конца номера
 * 
 * @param[in] buf Строка с номером телефона
 * @param[in] size Размер строки
 * @param[in,out] index Индекс начала строки (откуда начинаем проверять)
 * 
 * @returns
 * Правда или ложь
*/
bool correct_spacind_end(const char *buf, size_t size, size_t *index)
{
    //end of string
    bool eos = false;

    while (!eos)
    {
        if (buf[*index] == '\n' || buf[*index] == 0 || *index == size)
            eos = true;
        else if (!isspace(buf[*index]))
            return false;
        (*index)++;
    }
    return eos;
}

int is_code_contry_valid(const char *buf, size_t size, size_t *index)
{
    bool border_right = false;
    bool plus = false;
    bool is_all_zeros = true;

    while (!plus && *index < size)
    {
        if (buf[*index] == '+' && isdigit(buf[*index + 1]))
        {
            if (buf[*index + 1] != '0' && isdigit(buf[*index + 1]))
                is_all_zeros = false;
            plus = true;
        }
        else if (buf[*index] == '(')
            return COUNTRY_CODE_EMPTY;
        else
            return COUNTRY_CODE_ERROR;
        (*index)++;
    }

    for (;*index < size && !border_right;)
    {
        if (buf[*index] != '0' && isdigit(buf[*index]))
            is_all_zeros = false;
        if (!isdigit(buf[(*index)++]) && !isspace(buf[*index]))
            return false;
        else if (buf[*index] == '(')
            border_right = true;
    }
    if (plus && border_right && !is_all_zeros)
        return COUNTRY_CODE_VALID;

    return COUNTRY_CODE_ERROR;
}

bool is_code_operator_valid(const char *buf, size_t size, size_t *index)
{
    bool border_left = false;
    bool border_right = false;
    size_t last_index, count = 0;

    if (buf[(*index)++] == '(')
        border_left = true;

    last_index = *index;
    while (*index < last_index + OPERATOR_NUMBERS && !border_right && *index < size)
    {
        if (isdigit(buf[*index]))
        {
            count++;
        }
        if (!isdigit(buf[(*index)++]))
            return false;
        else if (buf[(*index)] == ')')
        {
            border_right = true;
        }
    }
    *index = *index + 1;
    return border_left && border_right && (count == 3);  
}

bool is_numbers_valid(const char *buf, size_t size_string, size_t size_of_numbers, size_t *index)
{
    size_t last_index;

    if (buf[(*index)++] != '-')
        return false;
    
    last_index = *index;
    while (*index < last_index + size_of_numbers)
    {
        if (!isdigit(buf[(*index)++]))
            return false;
    }

    if (buf[*index] == '\n' || buf[*index] == '-' || *index == size_string || isspace(buf[*index]))
    {
        // (*index)++;
        return true;
    }
    else
        return false;
}


bool is_number(const char *buf, size_t size)
{
    size_t index = 0, last_index;
    int rc;
    bool current_status = true;
    
    current_status = current_status && correct_spacesing(buf, size, &index);
    // printf("%d\n", correct_spacesing(buf, size, &index));
    index--;
    last_index = index;
    rc = is_code_contry_valid(buf, size, &index);
    switch (rc)
    {
        case COUNTRY_CODE_VALID:
            break;
        case COUNTRY_CODE_EMPTY:
            index = last_index;
            break;
        case COUNTRY_CODE_ERROR:
            return false;
        default:
            return false;
    }
    rc = true;
    
    // printf("%d\n", rc);
    // printf("%d\n", is_code_operator_valid(buf, size, &index));
    // printf("%zu::%c\n", index, buf[index]);
    // printf("%d\n", is_numbers_valid(buf, size, 3, &index));
    // printf("%zu::%c\n", index, buf[index]);
    // printf("%d\n", is_numbers_valid(buf, size, 2, &index)); 
    // printf("%d\n", is_numbers_valid(buf, size, 2, &index));
    // printf("%zu::%c\n", index, buf[index]);
    // printf("%d\n", correct_spacind_end(buf, size, &index));

    current_status = current_status && rc;
    current_status = current_status && is_code_operator_valid(buf, size, &index);
    current_status = current_status && is_numbers_valid(buf, size, 3, &index);
    current_status = current_status && is_numbers_valid(buf, size, 2, &index);
    current_status = current_status && is_numbers_valid(buf, size, 2, &index);
    current_status = current_status && correct_spacind_end(buf, size, &index);
    return current_status;
    // return rc && is_code_operator_valid(buf, size, &index) && is_numbers_valid(buf, size, 3, &index) && is_numbers_valid(buf, size, 2, &index) && is_numbers_valid(buf, size, 2, &index);
}