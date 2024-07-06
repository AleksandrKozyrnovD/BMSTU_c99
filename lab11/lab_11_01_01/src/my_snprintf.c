#include "my_snprintf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Функция для копирования строки
 *
 * @param[in,out] dst Место, куда копируем. Гарантируется, что ее размер больше или равен размеру src
 * @param[in] src Место, откуда копируем
 */
static void my_strcpy(char *dst, const char *src)
{
    while (*src)
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = *src; //Терминирующий нуль
}

// static int read_char(char *dst, int *size, char ch, int max)
// {
//     if (*size < max - 1)
//         dst[(*size)++] = ch;
//     return 1;
// }

/**
 * @brief Функция для записи (добавления) строчки в конец исходной строчки 
 *
 * @param[in,out] dst Дописываемая строчка
 * @param[in] src Какая строчка дописывается
 * @param[in,out] size Текущий размер dst
 * @param[in] max Максимальный размер dst
 * @return Кол-во прочитанных символов
 */
static int catstr(char *dst, const char *src, int *size, int max)
{
    int read = 0;
    // if (!src)
    // {
    //     char *nill = "(null)";
    //     while (*nill)
    //     {
    //         // read += read_char(dst, size, *nill, max);
    //         read++;
    //         if (*size < max - 1)
    //         {
    //             dst[*size] = *nill;
    //             (*size)++;
    //         }
    //         nill++;
    //     }
    // }
    // else
    // {
    while (*src)
    {
        // read += read_char(dst, size, *src, max);
        read++;
        if (*size < max - 1)
        {
            dst[*size] = *src;
            (*size)++;
        }
        src++;
    }
    // }
    return read;
}

/**
 * @brief Функция для подсчитывания логарифма числа (используется как счетчик кол-ва цифр)
 *
 * @param[in] base Основание логарифма
 * @param[in] integer Аргумент логарифма
 * @return Степень основания, чтобы получить integer
 */
static int my_log(size_t base, long long integer)
{
    //Если нуль, то кол-во цифр равно 1
    if (!integer)
        return 1;

    int power = 0;
    while (integer)
    {
        power++;
        integer /= base;
    }
    return power;
}

/**
 * @brief Функция для превращения числа в строчку
 *
 * @param[in,out] dst Куда дописывать число
 * @param[in,out] size Текущий размер dst
 * @param[in] integer Число
 * @param[in] base Основание числа (Система Счисления)
 * @param[in] max Максимальный размер dst
 * @return Количество прочитанных символов
 */
static int convert_to_int(char *dst, int *size, unsigned long long integer, int base, int max)
{
    char base_num[] = "0123456789ABCDEF";
    
    int power = my_log(base, integer);
    int overcapacity = 0;

    //Проверяем, сможем ли мы вместить все число в строчку
    //Если кол-во чисел + кол-во записанных чисел > максимальное - 1, то
    if (power + *size > max - 1)
    {
        //Недопрочитанных символов (overcapacity) = Основание - Максимальное + 1 + Размер
        //Основание (кол-во символов, которое влезет в строчку)(power) = Максимальное - 1 - текущий_размер
        overcapacity = power;
        power = max - 1 - *size;
        overcapacity -= power;
    }
    
    //Уменьшаем кол-во символов, пока не останется столько цифр, сколько влезет в строчку
    for (int i = 0; i < overcapacity; i++, integer /= base);

    for (int i = power; i != 0; i--)
    {
        //Если делить integer на его основание (в нашем случае основание равно 8, но примеры будут рассмотрены на 10),
        //и брать остаток, то это будет самый первый разряд числа. То есть 24 % 10 = 4.
        //Мы можем использовать этот остаток, чтобы взять его как индекс в массиве символов.
        //То есть base_num[24 % 10] == '4'.
        //Этим тут и пользуемся
        //
        //*size + i - 1 делаем потому, что заполняем справа-налево, а не наоборот. Иначе пришлось бы
        //переворачивать какую-то определенную зону строчки
        dst[*size + i - 1] = base_num[integer % base];
        integer /= base;
    }
    *size += power;

    // Кол-во записанных цифр + кол-во недозаписанных цифр
    return power + overcapacity;
}

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    // if (!s)
    //     return -1;
    
    int read = 0;
    const char *ptr = NULL;
    int size = 0; //Текущий заполненный размер (возвращаемый из функции)
    char *tmp = malloc((n + 1) * sizeof(char)); //С запасом
    if (!tmp)
        return -1;
    
    va_list arguments;

    va_start(arguments, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case 's':
                    ptr = va_arg(arguments, const char *);
                    // if (!ptr)
                    // {
                    //     free(tmp);
                    //     va_end(arguments);
                    //     return -1;
                    // }
                    read += catstr(tmp, ptr, &size, n);
                    break;
                case 'l':
                    //Проверка на %llo
                    if (*(format + 1) == 'l' && *(format + 2) == 'o')
                    {
                        format += 2;
                        read += convert_to_int(tmp, &size, va_arg(arguments, unsigned long long), 8, n);
                    }
                    break;
                case '%':
                    // read += read_char(tmp, &size, *format, n);
                    read++;
                    if (size < (int) n - 1)
                    {
                        tmp[size] = *format;
                        size++;
                    }
                    break;
                default:
                    tmp[size] = 0;
                    my_strcpy(s, tmp);
                    free(tmp);
                    va_end(arguments);
                    return -1;
            }
        }
        else
        {
            // read += read_char(tmp, &size, *format, n);
            read++;
            if (size < (int) n - 1)
            {
                tmp[size] = *format;
                size++;
            }
        }
        format++;
    }
       
    tmp[size] = 0;
    va_end(arguments);
    
    if (s != NULL)
        my_strcpy(s, tmp);
    free(tmp);

    return read;
}

