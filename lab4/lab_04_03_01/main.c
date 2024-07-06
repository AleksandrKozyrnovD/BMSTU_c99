#include "logic.h"
#include "inputoutput.h"

int main(void)
{
    char buffer[MAX_STRLEN];
    char words[MAX_STRLEN / 2][MAX_WORD_SIZE];
    char new_str[MAX_STRLEN];
    int return_code;
    size_t size = 0;

    return_code = get_line(buffer, MAX_STRLEN);
    switch (return_code)
    {
        case ERR_IO:
            // printf("Ошибка ввода\n");
            return return_code;
        case ERR_BUF_TOO_SMALL:
            // printf("Строка слишком большая\n");
            return return_code;
        case OK:
            break;
        default:
            // printf("Случилась непредвиденная ошибка\n");
            return return_code;
    }
    
    return_code = parse_string(buffer, words, &size);
    switch (return_code)
    {
        case ERR_TOO_MANY_WORDS:
            // printf("Слишком много слов\n");
            return return_code;
        case OK:
            break;
        default:
            // printf("Случилась непредвиденная ошибка\n");
            return return_code;
    }

    return_code = form_string(words, size, new_str, MAX_STRLEN);
    switch (return_code)
    {
        case ERR_BUF_TOO_SMALL:
            // printf("Строка слишком длинная\n");
            return return_code;
        case ERR_IO:
            // printf("В строчке 1 слово, нам нечего выводить!\n");
            return return_code;
        case OK:
            break;
        default:
            // printf("Непредвиденная ошибка\n");
            return return_code;
    }

    printf("Result: %s\n", new_str);

    return OK;
}
