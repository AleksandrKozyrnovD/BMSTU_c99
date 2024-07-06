#include <string.h>
#include <stdbool.h>
#include "process_text.h"


int prefix(char *string, char *prefix)
{
    if (strlen(prefix) > strlen(string))
        return 1;
    return strncmp(string, prefix, sizeof(*prefix));
}

int print_if_prefix(FILE *file_source, FILE *file_dest, char *pref)
{
    student_t student;
    bool flag = false;
    while (read_student(file_source, &student) == EXIT_SUCCESS)
    {
        // printf("%d\n%s::%s\n", prefix(student.familia, pref), student.familia, pref);
        if (prefix(student.familia, pref) == 0)
        {
            // print_student(stdout, &student);
            print_student(file_dest, &student);
            flag = true;
        }
    }
    if (flag)
        return EXIT_SUCCESS;
    return ERR_COMMAND;
}
