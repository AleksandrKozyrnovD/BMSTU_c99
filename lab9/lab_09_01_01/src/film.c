#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "film.h"

#define BUF_SIZE 128

int film_init_content(film_t *film, const char *title, const char *name, int year)
{
    size_t len = 0;
    char *name_tmp = NULL;
    char *title_tmp = strdup(title);
    if (!title_tmp)
        return ERR_MEM;
    
    len = strlen(title_tmp);
    if (title_tmp[len - 1] == '\n')
        title_tmp[--len] = 0;
    if (!len)
    {
        free(name_tmp);
        free(title_tmp);
        return ERR_IO;
    }
    name_tmp = strdup(name);
    if (!name_tmp)
    {
        free(title_tmp);
        // free(name_tmp);
        return ERR_MEM;
    }
    len = strlen(name_tmp);
    if (name_tmp[len - 1] == '\n')
        name_tmp[--len] = 0;
    if (!len)
    {
        free(name_tmp);
        free(title_tmp);
        return ERR_IO;
    }

    film->year = year;
    film->title = title_tmp;
    film->name = name_tmp;

    return EXIT_SUCCESSFUL;
}

int film_copy(const film_t *src, film_t *dst)
{
    return film_init_content(dst, src->title, src->name, src->year);
}

void film_free_content(film_t *film)
{
    free(film->name);
    free(film->title);
    film->name = NULL;
    film->title = NULL;
    film->year = 0;
}

int film_read(FILE *file, film_t *film)
{
    char buf_title[BUF_SIZE + 2], buf_name[BUF_SIZE + 2];
    size_t len;
    char tmp[2];
    int year;

    film->name = NULL;
    film->title = NULL;

    if (!fgets(buf_title, sizeof(buf_title), file))
        return ERR_IO;
    len = strlen(buf_title);
    if (buf_title[len - 1] == '\n')
        buf_title[--len] = 0;
    if (!len || len > BUF_SIZE)
        return ERR_IO;

    if (!fgets(buf_name, sizeof(buf_name), file))
        return ERR_IO;
    len = strlen(buf_name);
    if (buf_name[len - 1] == '\n')
        buf_name[--len] = 0;
    if (!len || len > BUF_SIZE)
        return ERR_IO;

    if (fscanf(file, "%d", &year) != 1)
        return ERR_IO;

    if (year < 0)
        return ERR_IO;
    fgets(tmp, sizeof(tmp), file);

    return film_init_content(film, buf_title, buf_name, year);
}

int film_read_ex(FILE *file, film_t *film)
{
    char *buf_name = NULL;
    char *buf_title = NULL; //Обязательно NULL
    size_t len = 0;
    ssize_t read /*, count*/;
    int year;

    int rc = EXIT_SUCCESSFUL;
    if ((read = getline(&buf_title, &len, file)) == -1)
    {
        free(buf_title);
        return ERR_IO;
    }
    if (!read || !len)
    {
        free(buf_name);
        free(buf_title);
        return ERR_IO;
    }
    if (buf_title[read - 1] == '\n')
        buf_title[--read] = 0;
    if (!read)
    {
        free(buf_name);
        free(buf_title);
        return CHECK_EOF;
    }
    if ((read = getline(&buf_name, &len, file)) == -1)
    {
        free(buf_name);
        free(buf_title);
        return ERR_IO;
    }
    if (!read)
    {
        free(buf_name);
        free(buf_title);
        return CHECK_EOF;
    }
    if (buf_name[read - 1] == '\n')
        buf_name[--read] = 0;
    if (!read)
    {
        free(buf_name);
        free(buf_title);
        return CHECK_EOF;
    }
    if (fscanf(file, "%d\n", &year) == 1)
    {
        if (year >= 0)
        {
            // printf("Year = %d\n", year);
            // rc = film_init_content(film, buf_title, buf_name, year);
            // free(buf_name);
            // free(buf_title);
            film->name = buf_name;
            film->title = buf_title;
            film->year = year;
            return rc;
        }
    }

    rc = ERR_IO;
    free(buf_name);
    free(buf_title);

    return rc;
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

