#define _GNU_SOURCE
#include "string.h"
#include "student.h"
#include "node.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

student_t *student_create(char *name, int mark)
{
    student_t *student = malloc(sizeof(student_t));
    if (!student)
        return NULL;
    
    student->name = name;
    student->mark = mark;

    return student;
}

errors_t student_read(FILE *file, student_t *student)
{
    int mark;
    char *name = NULL;
    ssize_t read = 0;
    size_t len = 0;
    if (fscanf(file, " %d", &mark) != 1)
        return ERR_IO;
    
    read = getline(&name, &len, file);
    if (read <= 0)
        return ERR_MEM;

    if (name[read - 1] == '\n')
        name[--read] = 0;

    if (!read)
    {
        free(name);
        return ERR_IO;
    }
    
    student->name = name;
    student->mark = mark;

    return EXIT_SUCCESSFUL;
}

errors_t student_read_ex(FILE *file, student_t **student)
{
    int mark;
    char *name = NULL;
    ssize_t read = 0;
    size_t len = 0;
    if (fscanf(file, " %d", &mark) != 1)
        return ERR_IO;
    
    read = getline(&name, &len, file);
    if (read <= 0)
        return ERR_MEM;

    if (name[read - 1] == '\n')
        name[--read] = 0;

    if (!read)
    {
        free(name);
        return ERR_IO;
    }
    
    *student = student_create(name, mark);
    if (!student)
    {
        free(name);
        return ERR_MEM;
    }

    return EXIT_SUCCESSFUL;
}

void student_print(FILE *file, const student_t *student)
{
    fprintf(file, "%d%s\n", student->mark, student->name);
}

int student_cmp(const void *left, const void *right)
{
    const student_t *l = left;
    const student_t *r = right;
    
    int score = l->mark - r->mark;
    if (!score)
        score = strcmp(l->name, r->name);

    return score;
}

int student_cmp_explicit(const void *left, const void *right)
{
    const student_t *l = left;
    const student_t *r = right;
    
    return l->mark - r->mark;
}

void student_free(student_t *student)
{
    // if (!student)
    //     return;
    free(student->name);
    free(student);
}

void node_print(FILE *file, const node_t *node)
{
    //печать только структур "стувдевнтны"
    student_print(file, (student_t *) node->data);
}

