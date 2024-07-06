#include <stdio.h>
#include "structures.h"



int get_student_by_pos(FILE *file, long pos, student_t *student)
{
    if (fseek(file, pos * sizeof(student_t), SEEK_SET) != 0)
        return ERR_IO;
    
    if (fread(student, sizeof(student_t), 1, file) != 1)
        return ERR_IO;
    return EXIT_SUCCESS;
}

int put_student_by_pos(FILE *file, long pos, student_t *student)
{
    if (fseek(file, pos * sizeof(student_t), SEEK_SET) != 0)
        return ERR_IO;
    
    if (fwrite(student, sizeof(student_t), 1, file) != 1)
        return ERR_IO;
    return EXIT_SUCCESS;
}


int sorted(FILE *file, long size)
{
    student_t student_i, student_j;
    for (long i = 0; i < size - 1; i++)
    {
        long min_index = i;
        for (long j = i + 1; j < size; j++)
        {
            if (get_student_by_pos(file, min_index, &student_i) != EXIT_SUCCESS)
                return ERR_IO;
            if (get_student_by_pos(file, j, &student_j) != EXIT_SUCCESS)
                return ERR_IO;

            if (cmp_by_family_stud(&student_i, &student_j) > 0)
                min_index = j;
            else if (cmp_by_family_stud(&student_i, &student_j) == 0)
            {
                if (cmp_by_name_stud(&student_i, &student_j) > 0)
                    min_index = j;
            }
        }
        if (min_index != i)
        {
            if (get_student_by_pos(file, min_index, &student_i) != EXIT_SUCCESS)
                return ERR_IO;
            if (get_student_by_pos(file, i, &student_j) != EXIT_SUCCESS)
                return ERR_IO;

            if (put_student_by_pos(file, min_index, &student_j) != EXIT_SUCCESS)
                return ERR_IO;
            if (put_student_by_pos(file, i, &student_i) != EXIT_SUCCESS)
                return ERR_IO;
        }
    }
    return EXIT_SUCCESS;
}

int sort_students_in_file(FILE *file)
{
    long size;

    if (fseek(file, 0, SEEK_END) != 0)
        return ERR_FILE;
    
    size = ftell(file);
    if (size < 0)
        return ERR_FILE;
    
    if (size % sizeof(student_t) != 0)
        return ERR_FILE;

    size = size / sizeof(student_t);

    if (sorted(file, size) != EXIT_SUCCESS)
        return ERR_FILE;

    return EXIT_SUCCESS;
}

//функция для записи в двоичный файл по позе
int write_student_bin(FILE *file, long pos, const student_t *student)
{
    if (fseek(file, pos * sizeof(student_t), SEEK_SET) != 0)
        return ERR_IO;
    
    if (fwrite(student, sizeof(*student), 1, file) != 1)
        return ERR_IO;
    return EXIT_SUCCESS;
}

//для чтения полностью
int print_bin(FILE *file_source, FILE *file_dst)
{
    student_t student;
    if (fseek(file_source, 0, SEEK_SET) != 0)
        return ERR_IO;
    
    if (ftell(file_source) % sizeof(student_t) != 0)
        return ERR_IO;

    while (fread(&student, sizeof(student), 1, file_source) == 1)
    {
        print_student(file_dst, &student);
    }

    return EXIT_SUCCESS;
}
