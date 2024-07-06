#include <stdio.h>
#include <string.h>
#include "additionals.h"
#include "errorcode.h"

int main(int argc, char **argv)
{
    int rc;

    if (argc != 4)
    {
        return 1;
    }

    if (strcmp(argv[1], "t2b") == 0)
    {
        FILE *file_source = fopen(argv[2], "rt");
        if (file_source == NULL)
            return ERR_FILE;
        FILE *file_dst = fopen(argv[3], "wb");
        if (file_dst == NULL)
        {
            fclose(file_source);
            return ERR_FILE;
        }
        rc = t2b(file_source, file_dst);
        fclose(file_source);
        fclose(file_dst);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    else if (strcmp(argv[1], "b2t") == 0)
    {
        FILE *file_source = fopen(argv[2], "rb");
        if (file_source == NULL)
            return ERR_FILE;
        FILE *file_dst = fopen(argv[3], "wt");
        if (file_dst == NULL)
        {
            fclose(file_source);
            return ERR_FILE;
        }
        rc = b2t(file_source, file_dst);
        fclose(file_source);
        fclose(file_dst);
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    return EXIT_SUCCESS;
}
