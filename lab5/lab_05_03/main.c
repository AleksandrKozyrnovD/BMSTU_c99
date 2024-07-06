#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "errorcode.h"
// #include "additionals.h"


int main(int argc, char **argv)
{
    int rc;

    if (argc == 4)
    {
        if (strcmp("c", argv[1]) == 0)
        {
            int count = atoi(argv[2]);
            if (count < 1)
                return ERR_INCORRECT_KEYS;
            
            FILE *file = fopen(argv[3], "wb");
            if (file == NULL)
                return ERR_FILE;
            rc = create_file(file, count);
            fclose(file);

            switch (rc)
            {
                // case ERR_FILE:
                //     printf("That file cannot be created\n");
                //     return rc;
                // case ERR_IO:
                //     printf("Cannot write into file\n");
                //     return rc;
                case EXIT_SUCCESS:
                    break;
                default:
                    return rc;
            }
        }
        // else if (strcmp(argv[1], "t2b") == 0)
        // {
        //     FILE *file_source = fopen(argv[2], "rt");
        //     if (file_source == NULL)
        //         return ERR_FILE;
        //     FILE *file_dst = fopen(argv[3], "wb");
        //     if (file_dst == NULL)
        //     {
        //         fclose(file_source);
        //         return ERR_FILE;
        //     }
        //     rc = t2b(file_source, file_dst);
        //     fclose(file_source);
        //     fclose(file_dst);
        //     if (rc != EXIT_SUCCESS)
        //         return rc;
        // }
        // else if (strcmp(argv[1], "b2t") == 0)
        // {
        //     FILE *file_source = fopen(argv[2], "rb");
        //     if (file_source == NULL)
        //         return ERR_FILE;
        //     FILE *file_dst = fopen(argv[3], "wt");
        //     if (file_dst == NULL)
        //     {
        //         fclose(file_source);
        //         return ERR_FILE;
        //     }
        //     rc = b2t(file_source, file_dst);
        //     fclose(file_source);
        //     fclose(file_dst);
        //     if (rc != EXIT_SUCCESS)
        //         return rc;
        // }
        else
            return ERR_INCORRECT_KEYS;
    }
    else if (argc == 3)
    {
        if (strcmp("p", argv[1]) == 0)
        {
            FILE *file = fopen(argv[2], "rb");
            if (file == NULL)
                return ERR_FILE;
            rc = print_file(file, stdout);
            fclose(file);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
        else if (strcmp("s", argv[1]) == 0)
        {
            FILE *file = fopen(argv[2], "r+");
            if (file == NULL)
                return ERR_FILE;
            rc = sort_file(file);
            fclose(file);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
        else
            return ERR_INCORRECT_KEYS;
    }
    else
        return ERR_INCORRECT_KEYS;

    return EXIT_SUCCESS;
}
