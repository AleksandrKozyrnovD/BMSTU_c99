#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "err.h"
#include "filter.h"
#include <dlfcn.h>
// #include "processlib.h"

typedef void (*print)(FILE *, const int *, const int *);

typedef int (*count_int)(FILE *);

typedef int (*fill_array)(FILE *, int *, int *);

typedef int (*filter)(const int *, const int *, int *);

typedef int (*get_size)(const int *, const int *);

typedef const int *(*minmax)(const int *, const int *);

typedef int (*comparator_t)(const void *, const void *);

typedef void (*sort)(void *, size_t, size_t, comparator_t);


int main(int argc, char **argv)
{

    void *lib = NULL;
    print print;
    count_int count_int;
    fill_array fill_array;
    filter key;
    get_size get_filtered_size;
    minmax min_func;
    minmax max_func;
    comparator_t compare_int;
    sort mysort;

    lib = dlopen("out/libprocess.so", RTLD_NOW);
    if (!lib)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    print = dlsym(lib, "print");
    if (!print)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    count_int = dlsym(lib, "count_int");
    if (!count_int)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    fill_array = dlsym(lib, "fill_array");
    if (!fill_array)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    key = dlsym(lib, "key");
    if (!key)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    get_filtered_size = dlsym(lib, "get_filtered_size");
    if (!get_filtered_size)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    min_func = dlsym(lib, "get_min");
    if (!min_func)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    max_func = dlsym(lib, "get_max");
    if (!max_func)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    compare_int = dlsym(lib, "compare_int");
    if (!compare_int)
    {
        dlclose(lib);
        return ERR_MEM;
    }
    mysort = dlsym(lib, "mysort");
    if (!mysort)
    {
        dlclose(lib);
        return ERR_MEM;
    }

    int *pbeg = NULL, *pend = NULL, rc = EXIT_SUCCESSFUL;
    int *filtered_b = NULL, *filtered_e;
    size_t size = 0, size_filtered = 0;
    FILE *file_read = NULL, *file_out = NULL;

    const int *min = NULL;
    const int *max = NULL;

    if (argc != 4 && argc != 3)
        return ERR_ARGS;
    
    if (!rc)
    {
        file_read = fopen(argv[1], "r");
        if (!file_read)
            return ERR_FILE;
    }
    if (!rc)
    {
        file_out = fopen(argv[2], "w");
        if (!file_out)
        {
            fclose(file_read);
            return ERR_FILE;
        }
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
                min = min_func(pbeg, pend);
                max = max_func(pbeg, pend);
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
    
    dlclose(lib);

    return rc;
}

