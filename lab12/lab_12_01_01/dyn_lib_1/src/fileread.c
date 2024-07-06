#include "fileread.h"
#include <stdio.h>
#include <stdlib.h>

void print(FILE *file, const int *pbeg, const int *pend)
{
    const int *pcur = pbeg;
    // fprintf(file, "Array: \n");
    while (pcur < pend)
    {
        fprintf(file, "%d ", *pcur);
        pcur++;
    }
    fprintf(file, "\n");
}

// static int count_int1(FILE *file, size_t *size)
// {
//     int rc = EXIT_SUCCESSFUL, num;
//     if (fseek(file, 0, SEEK_SET) != 0)
//         return ERR_FILE;
//
//     *size = 0;
//
//     while (rc == EXIT_SUCCESSFUL)
//     {
//         if (fscanf(file, "%d", &num) != 1)
//             rc = ERR_IO;
//         else
//             (*size)++;
//     }
//     
//     if (feof(file))
//         rc = EXIT_SUCCESSFUL;
//
//     rewind(file);
//     if (*size == 0)
//         return EMPTY;
//
//     return rc;
// }

size_t count_int(FILE *file)
{
    int num;
    size_t size = 0;

    while (fscanf(file, "%d", &num) == 1)
        size++;

    return size;
}

int fill_array(FILE *file, int *pbeg, int *pend)
{
    int num;
    int rc = EXIT_SUCCESSFUL;
    for (int *pcur = pbeg; pcur <= pend && !rc; pcur++)
    {
        if (fscanf(file, "%d", &num) != 1)
            rc = ERR_IO;
        else
            *pcur = num;
    }
    if (rc != EXIT_SUCCESSFUL && feof(file))
        rc = EXIT_SUCCESSFUL;

    return rc;
}

// int read_into_array(FILE *file, int **pbeg, int **pend)
// {
//     int rc = EXIT_SUCCESSFUL;
//     size_t size = 0;

//     rewind(file);
//     size = count_int(file);
//     if (size == 0)
//         return EMPTY;
//     rewind(file);

//     *pbeg = (int *)malloc(size * sizeof(int));
//     if (*pbeg == NULL)
//         return ERR_MEM;
//     *pend = *pbeg + size;

//     for (int *pcur = *pbeg; pcur <= *pend && !rc; pcur++)
//     {
//         if (fscanf(file, "%d", pcur) != 1)
//             rc = ERR_IO;
//     }
//     if (rc != EXIT_SUCCESSFUL && feof(file))
//         rc = EXIT_SUCCESSFUL;

//     return fill_array(file, *pbeg, *pend);
// }

// int read_into_array(FILE *file, int **array, size_t *size)
// {
//     int rc = EXIT_SUCCESSFUL;
//     // if ((rc = count_int(file, size)))
//     //     return rc;
//     
//     // if ((rc = count_int1(file, size)))
//     //     return rc;
//     // printf("Size = %zu\n", *size);
//     rewind(file);
//     *size = count_int(file);
//     rewind(file);
//     if (*size == 0)
//         return EMPTY;
//
//     *array = (int *)malloc(*size * sizeof(int));
//     if (*array == NULL)
//         return ERR_MEM;
//     
//     for (size_t i = 0; i < *size + 1 && !rc; i++)
//     {
//         // printf("Rc = %d\n", rc);
//         if (fscanf(file, "%d", *array + i) != 1)
//             rc = ERR_IO;
//         // if (i > *size && rc == EXIT_SUCCESSFUL) //Если было прочитано лишнее число за границами выделенной памяти, то ошибка. Пример: 1 2 a 3 4 --> 1 2 3 будет прочитано, хотя выделено на 2
//         //     rc = ERR_IO;
//     }
//     if (rc != EXIT_SUCCESSFUL && feof(file))
//         rc = EXIT_SUCCESSFUL;
//
//
//     return rc;
// }

