#include "logic.h"
#include "inputoutput.h"

int main(void)
{
    char buffer1[MAX_STRLEN], buffer2[MAX_STRLEN];
    char words1[MAX_COUNT_WORDS][MAX_WORD_SIZE], words2[MAX_COUNT_WORDS][MAX_WORD_SIZE];
    int return_code;
    size_t size1 = 0, size2 = 0;

    return_code = get_line(buffer1, MAX_STRLEN);
    switch (return_code)
    {
        // case ERR_IO:
        //     // printf("Ошибка ввода\n");
        //     return return_code;
        // case ERR_BUF_TOO_SMALL:
        //     // printf("Строка слишком большая\n");
        //     return return_code;
        case OK:
            break;
        default:
            // printf("Случилась непредвиденная ошибка\n");
            return return_code;
    }

    return_code = get_line(buffer2, MAX_STRLEN);
    switch (return_code)
    {
        // case ERR_IO:
        //     // printf("Ошибка ввода\n");
        //     return return_code;
        // case ERR_BUF_TOO_SMALL:
        //     // printf("Строка слишком большая\n");
        //     return return_code;
        case OK:
            break;
        default:
            // printf("Случилась непредвиденная ошибка\n");
            return return_code;
    }

    if (buffer1[0] == 0 || buffer2[0] == 0)
    {
        // printf("Одна из строк пустая\n");
        return ERR_STRING_IS_EMPTY;
    }
    
    return_code = parse_string(buffer1, words1, &size1);
    switch (return_code)
    {
        // case ERR_TOO_MANY_WORDS:
        //     // printf("Слишком много слов\n");
        //     return return_code;
        // case ERR_IO:
        //     // printf("В строчке(-ах) нет подходящих слов\n");
        //     return return_code;
        case OK:
            break;
        default:
            // printf("Случилась непредвиденная ошибка\n");
            return return_code;
    }

    return_code = parse_string(buffer2, words2, &size2);
    switch (return_code)
    {
        // case ERR_TOO_MANY_WORDS:
        //     // printf("Слишком много слов\n");
        //     return return_code;
        case OK:
            break;
        default:
            // printf("Случилась непредвиденная ошибка\n");
            return return_code;
    }

    if (print_uniq(words1, size1, words2, size2) != OK)
    {
        // printf("Ошибка! Нет уникальных слов\n");
        return ERR_IO;
    }
    return OK;
}