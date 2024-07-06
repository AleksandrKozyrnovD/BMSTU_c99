#include <string.h>
#include "structures.h"


int read_student(FILE *file, student_t *student)
{
    char family[FAMILY_LEN + 2];
    char name[NAME_LEN + 2];
    size_t lenght;
    char temp[2];
    uint32_t marks[N_MARKS];

    // printf("Input a name: \n");
    if (!fgets(family, sizeof(family), file))
    {
        // printf("Error at read_student, cant get familia\n");
        return ERR_IO;
    }
    lenght = strlen(family);
    if (family[lenght - 1] == '\n')
    {
        family[lenght - 1] = 0;
        lenght--;
    }
    if (!lenght || lenght > FAMILY_LEN)
    {
        // printf("Error at read_student, familia has no lenght\n");
        return ERR_STRING_TOO_BIG;
    }
    // fgets(temp, sizeof(temp), file);

    if (!fgets(name, sizeof(name), file))
    {
        // printf("Error at read_student, cant read name\n");
        return ERR_IO;
    }
    lenght = strlen(name);
    if (name[lenght - 1] == '\n')
    {
        name[lenght - 1] = 0;
        lenght--;
    }
    if (!lenght || lenght > NAME_LEN)
    {
        // printf("Error at read_student, name has no lenght");
        return ERR_STRING_TOO_BIG;
    }

    size_t counter = 0;
    // uint32_t mark;
    for (size_t i = 0; i < N_MARKS; i++)
    {
        if (fscanf(file, "%u", &marks[counter++]) != 1)
        {
            // printf("Error at read_student, cant read marks\n");
            return ERR_IO;
        }
    }

    if (counter != N_MARKS)
    {
        // printf("Error at read_student, now nmarks\n");
        return ERR_IO;
    }
    
    strcpy(student->familia, family);
    strcpy(student->name, name);
    memcpy(student->marks, marks, sizeof(marks));
    fgets(temp, sizeof(temp), file);

    return EXIT_SUCCESS;
}


void print_student(FILE *file, const student_t *student)
{
    fprintf(file, "%s\n%s\n", student->familia, student->name);
    for (size_t i = 0; i < N_MARKS; i++)
    {
        fprintf(file, "%u ", *(student->marks + i));
    }
    fprintf(file, "\n");
}

int cmp_by_family_stud(const student_t *left, const student_t *right)
{
    return strcmp(left->familia, right->familia);
}

int cmp_by_name_stud(const student_t *left, const student_t *right)
{
    return strcmp(left->name, right->name);
}
