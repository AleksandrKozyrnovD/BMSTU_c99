#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "process_bin.h"
#include "process_text.h"
#include "errorcode.h"
// #include "additionals.h"


int main(int argc, char **argv)
{
    switch (argc)
    {
        case 5:
            {
                if (strcmp(argv[1], "ft") == 0)
                {
                    FILE *file_source = fopen(argv[2], "rt");
                    if (file_source == NULL)
                        return ERR_FILE;
                    FILE *file_dst = fopen(argv[3], "wt");
                    if (file_dst == NULL)
                    {
                        fclose(file_source);
                        return ERR_FILE;
                    }
                    int rc = print_if_prefix(file_source, file_dst, argv[4]);
                    fclose(file_source);
                    fclose(file_dst);
                    if (rc != EXIT_SUCCESS)
                        return rc;
                    break;
                }
                else
                    return ERR_TASK;
            }
        // case 4:
        //     {
        //         if (strcmp(argv[1], "t2b") == 0)
        //         {
        //             FILE *file_source = fopen(argv[2], "rt");
        //             if (file_source == NULL)
        //                 return ERR_FILE;
        //             FILE *file_dst = fopen(argv[3], "wb");
        //             if (file_dst == NULL)
        //             {
        //                 fclose(file_source);
        //                 return ERR_FILE;
        //             }
        //             int rc = t2b(file_source, file_dst);
        //             fclose(file_source);
        //             fclose(file_dst);
        //             // printf("Correct transform tp binary\n");
        //             if (rc != EXIT_SUCCESS)
        //                 return rc;
        //             break;
        //         }
        //         else if (strcmp(argv[1], "b2t") == 0)
        //         {
        //             FILE *file_source = fopen(argv[2], "rb");
        //             if (file_source == NULL)
        //                 return ERR_FILE;
        //             FILE *file_dst = fopen(argv[3], "wt");
        //             if (file_dst == NULL)
        //             {
        //                 fclose(file_source);
        //                 return ERR_FILE;
        //             }
        //             int rc = b2t(file_source, file_dst);
        //             fclose(file_source);
        //             fclose(file_dst);
        //             // printf("Correct transform binary to text\n");
        //             if (rc != EXIT_SUCCESS)
        //                 return rc;
        //             break;
        //         }
        //         else
        //             return ERR_TASK;
        //     }
        case 3:
            {
                if (strcmp(argv[1], "sb") == 0)
                {
                    FILE *file = fopen(argv[2], "rb+");
                    if (file == NULL)
                        return ERR_FILE;
                    int rc = sort_students_in_file(file);
                    fclose(file);
                    if (rc != EXIT_SUCCESS)
                        return rc;
                    break;
                }
                else
                    return ERR_TASK;
            }
        default:
            return ERR_TASK;
    }

    return EXIT_SUCCESS;
}
