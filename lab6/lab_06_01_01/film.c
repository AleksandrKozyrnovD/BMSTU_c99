#include <string.h>
#include "error.h"
#include "film.h"

/**
 * @brief Функция для проверки чтения строки файла в поле типа char *
 *
 * @param[in] file поток ввода
 * @param[out] buffer поле типа char *
 * @param[in] len длина buffer
 * @param[in] desired_len желаемая длина buffer. При ее превышении будет выдана ошибка
 * @return код ошибки
 */
static int check_correct(FILE *file, char *buffer, size_t len, size_t desired_len)
{
    size_t len_current = 0;
    if (fgets(buffer, len, file) == NULL)
        return ERR_IO;

    len_current = strlen(buffer);
    if (len_current && buffer[len_current - 1] == '\n')
        buffer[--len_current] = 0; //NULL

    if (!len_current)
        return CHECK_EOF;

    if (len_current > desired_len)
        return ERR_RANGE;

    return EXIT_SUCCESSFUL;
}

int film_read(FILE *file, film_t *film)
{
    char buffer_name[NAME_LEN + 5];
    char buffer_title[TITLE_LEN + 5];
    char temp[2];
    int year;
    int rc;

    rc = check_correct(file, buffer_title, sizeof(buffer_title), TITLE_LEN);
    if (rc == CHECK_EOF)
    {
        rc = check_correct(file, buffer_name, sizeof(buffer_name), NAME_LEN);
        if (rc != EXIT_SUCCESSFUL && feof(file))
            return CHECK_EOF;
    }
    else if (rc == EXIT_SUCCESSFUL)
    {
        rc = check_correct(file, buffer_name, sizeof(buffer_name), NAME_LEN);
    }
    else
        return rc;
    if (rc != EXIT_SUCCESSFUL)
        return rc;

    if (fscanf(file, "%d", &year) != 1)
        return ERR_IO;
    if (year < 0)
        return ERR_RANGE;

    fgets(temp, sizeof(temp), file);

    strcpy(film->title, buffer_title);
    strcpy(film->name, buffer_name);
    film->year = year;

    return EXIT_SUCCESSFUL;
}

void film_print(FILE *file, const film_t *film)
{
    fprintf(file, "%s\n%s\n%d\n", film->title, film->name, film->year);
}

int film_cmp_name(const film_t *left, const film_t *right)
{
    int compare_score = strcmp(left->name, right->name);
    if (compare_score != 0)
        return compare_score;
    compare_score = left->year - right->year;
    if (compare_score != 0)
        return compare_score;
    compare_score = strcmp(left->title, right->title);
    return compare_score;
    // return strcmp(left->name, right->name);
}

int film_cmp_title(const film_t *left, const film_t *right)
{
    int compare_score = strcmp(left->title, right->title);
    if (compare_score != 0)
        return compare_score;
    compare_score = strcmp(left->name, right->name);
    if (compare_score != 0)
        return compare_score;
    compare_score = left->year - right->year;
    return compare_score;
}

int film_cmp_year(const film_t *left, const film_t *right)
{
    int compare_score = left->year - right->year;
    if (compare_score != 0)
        return compare_score;
    compare_score = strcmp(left->title, right->title);
    if (compare_score != 0)
        return compare_score;
    compare_score = strcmp(left->name, right->name);
    return compare_score;
}

int film_cmp_name_explicit(const film_t *left, const film_t *right)
{
    return strcmp(left->name, right->name);
}

int film_cmp_title_explicit(const film_t *left, const film_t *right)
{
    return strcmp(left->title, right->title);
}

int film_cmp_year_explicit(const film_t *left, const film_t *right)
{
    return left->year - right->year;
}
