#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.h"
#include "processlib.h"
// #include "comparator.h"
// #include "err.h"
// #include "fileread.h"
// #include "filter.h"
// #include "sort.h"


int main(int argc, char **argv)
{
    int *pbeg = NULL, *pend = NULL, rc = EXIT_SUCCESSFUL;
    int *filtered_b = NULL, *filtered_e;
    size_t size = 0, size_filtered = 0;

    const int *min = NULL;
    const int *max = NULL;

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
    
    size = count_int(file_read);
    if (!size)
        rc = EMPTY;
    rewind(file_read);
    if (!rc)
    {
        pbeg = malloc(size * sizeof(int));
        if (!pbeg)
            rc = ERR_MEM;
        else
            pend = pbeg + size;
    }

    if (!rc)
        rc = fill_array(file_read, pbeg, pend);
    
    if (!rc)
    {
        if (argc == 3)
        {
            mysort(pbeg, size, sizeof(int), compare_int);
            print(file_out, pbeg, pend);
        }
        else
        {
            if (strcmp(argv[3], "f") == 0)
            {
                min = get_min(pbeg, pend);
                max = get_max(pbeg, pend);
                size_filtered = get_filtered_size(max, min);
                if (!size)
                    rc = EMPTY;
                if (!rc)
                {
                    filtered_b = malloc(size_filtered * sizeof(int));
                    if (!filtered_b)
                        rc = ERR_MEM;
                    else
                        filtered_e = filtered_b + size_filtered;
                    // key(pbeg, pend, filtered_b, size_filtered);
                    rc = key(pbeg, pend, filtered_b);
                    if (!rc)
                    {
                        mysort(filtered_b, size_filtered, sizeof(int), compare_int);
                        print(file_out, filtered_b, filtered_e);
                    }
                }
            }
            else
            {
                rc = ERR_ARGS;
            }
        }
    }
    fclose(file_read);
    fclose(file_out);

    free(pbeg);
    free(filtered_b);

    return rc;
}

