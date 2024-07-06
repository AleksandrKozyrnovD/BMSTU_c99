#include "additionals.h"
#include "structures.h"


int b2t(FILE *file_source, FILE *file_dst)
{
    if (fseek(file_source, 0, SEEK_END) != 0)
        return ERR_IO;
    
    long size = ftell(file_source);
    if (size == -1)
        return ERR_FILE;
    
    if (size % sizeof(student_t) != 0)
        return ERR_IO;
    
    if (fseek(file_source, 0, SEEK_SET) != 0)
        return ERR_IO;
    
    student_t student;

    size = size / sizeof(student_t);
    for (long i = 0; i < size; i++)
    {
        if (fread(&student, sizeof(student_t), 1, file_source) != 1)
            return ERR_IO;
        print_student(file_dst, &student);
    }

    return EXIT_SUCCESS;
}

//text to binary
int t2b(FILE *file_source, FILE *file_dst)
{
    if (fseek(file_source, 0, SEEK_END) != 0)
        return ERR_IO;
    
    if (fseek(file_source, 0, SEEK_SET) != 0)
        return ERR_IO;

    student_t student;
    while (read_student(file_source, &student) == EXIT_SUCCESS)
    {
        // print_student(stdout, &student);
        if (fwrite(&student, sizeof(student_t), 1, file_dst) != 1)
            return ERR_IO;
    }

    return EXIT_SUCCESS;
}
