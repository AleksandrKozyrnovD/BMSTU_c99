#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparator.h"
#include "fileread.h"
#include "filter.h"
#include "sort.h"


int main(int argc, char **argv)
{
    // int *array = NULL, rc;
    int *pbeg = NULL, *pend = NULL, rc;
    int *filtered_b = NULL, *filtered_e;
    // size_t size = 0;
    if (argc != 4 && argc != 3)
        return ERR_ARGS;
    
    FILE *file_read = fopen(argv[1], "r");
    if (!file_read)
        return ERR_FILE;

    FILE *file_out = fopen(argv[2], "w");
    if (!file_out)
    {
        fclose(file_read);
        return ERR_FILE;
    }

    rc = read_into_array(file_read, &pbeg, &pend);
    if (argc == 4 && !rc)
    {
        if (strcmp(argv[3], "f") != 0)
            rc = ERR_ARGS;
        else
        {
            rc = key(pbeg, pend, &filtered_b, &filtered_e);
            if (!rc)
            {
                free(pbeg);
                pbeg = filtered_b;
                pend = filtered_e;
                filtered_b = NULL;
            }
        }
    }
    
    if (!rc)
    {
        mysort(pbeg, pend - pbeg, sizeof(int), compare_int);
        print(file_out, pbeg, pend);
    }
    
    fclose(file_read);
    fclose(file_out);
    if (pbeg)
        free(pbeg);
    if (filtered_b)
        free(filtered_b);

    return rc;
    // switch (argc)
    // {
    //     case 3:
    //         // rc = read_into_array(file_read, &array, &size);
    //         rc = read_into_array(file_read, &pbeg, &pend);
    //         switch (rc)
    //         {
    //             case EXIT_SUCCESSFUL:
    //                 // mysort(array, size, sizeof(int), compare_int);
    //                 mysort(pbeg, pend - pbeg, sizeof(int), compare_int);
    //                 // print(file_out, array, array + size);
    //                 print(file_out, pbeg, pend);
    //                 break;
    //             default:
    //                 break;
    //         }
    //         break;
    //     case 4:
    //         if (strcmp(argv[3], "f") != 0)
    //         {
    //             rc = ERR_ARGS;
    //             break;
    //         }
    //         // rc = read_into_array(file_read, &array, &size);
    //         rc = read_into_array(file_read, &pbeg, &pend);
    //         switch (rc)
    //         {
    //             case EXIT_SUCCESSFUL:
    //                 // rc = key(array, array + size, &filtered_b, &filtered_e);
    //                 rc = key(pbeg, pend, &filtered_b, &filtered_e);
    //                 if (rc != EXIT_SUCCESSFUL)
    //                     break;
    //                 mysort(filtered_b, filtered_e - filtered_b, sizeof(int), compare_int);
    //                 print(file_out, filtered_b, filtered_e);
    //                 break;
    //             default:
    //                 break;
    //         }
    //         break;
    //     default:
    //         rc = ERR_ARGS;
    //         break;
    // }
    // if (array)
    //     free(array);
}

