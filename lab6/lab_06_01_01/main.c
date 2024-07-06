#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "error.h"
#include "film_array.h"

static int check_int(const char *buffer)
{
    int rc = EXIT_SUCCESSFUL;

    for (int i = 0; buffer[i] != 0 && rc == EXIT_SUCCESSFUL; i++)
    {
        if (!isdigit(buffer[i]))
            rc = ERR_ARGS;
    }
    
    return rc;
}

int main(int argc, char **argv)
{
    film_t films[MAX_N];
    int choice, rc = EXIT_SUCCESSFUL;
    comparator_t cmp;
    size_t size = 0;

    if (argc < 2)
        return ERR_ARGS;

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
        return ERR_ARGS;

    switch (argc)
    {
        case 3:
            choice = get_choice_by_name(argv[2]);
            // if (choice == ERR_CHOICE)
            //     return ERR_CHOICE;
            
            switch (choice)
            {
                case TITLE_CHOICE:
                    cmp = film_cmp_title;
                    break;
                case NAME_CHOICE:
                    cmp = film_cmp_name;
                    break;
                case YEAR_CHOICE:
                    cmp = film_cmp_year;
                    break;
                default:
                    return ERR_CHOICE;
            }
            rc = film_array_read(file, films, &size, MAX_N, cmp);
            // printf("Rc = %d\n", rc);
            if (rc == EXIT_SUCCESSFUL)
                film_array_print(stdout, films, size);
            break;
        case 4:
            choice = get_choice_by_name(argv[2]);
            // if (choice == ERR_CHOICE)
            //     return ERR_CHOICE;
            switch (choice)
            {
                case TITLE_CHOICE:
                    cmp = film_cmp_title_explicit;
                    break;
                case NAME_CHOICE:
                    cmp = film_cmp_name_explicit;
                    break;
                case YEAR_CHOICE:
                    cmp = film_cmp_year_explicit;
                    break;
                default:
                    return ERR_CHOICE;
            }
            rc = film_array_read(file, films, &size, MAX_N, cmp);
            if (rc == EXIT_SUCCESSFUL)
            {
                film_t film;
                film_t what;
                switch (choice)
                {
                    case TITLE_CHOICE:
                        // rc = film_array_search_title(films, size, &film, argv[3]);
                        // what.title = argv[3];
                        if (sscanf(argv[3], "%s", what.title) != 1)
                            return ERR_ARGS;
                        break;
                    case NAME_CHOICE:
                        // rc = film_array_search_name(films, size, &film, argv[3]);
                        // what.name = argv[2];
                        if (sscanf(argv[3], "%s", what.name) != 1)
                            return ERR_ARGS;
                        break;
                    case YEAR_CHOICE:
                        if (check_int(argv[3]) != EXIT_SUCCESSFUL)
                            return ERR_ARGS;
                        // rc = film_array_search_year(films, size, &film, atoi(argv[3]));
                        what.year = atoi(argv[3]);
                        break;
                }

                rc = film_array_search(films, size, &film, &what, cmp);
                if (rc == EXIT_SUCCESSFUL)
                    film_print(stdout, &film);
                else if (rc == NOT_FOUND)
                {
                    printf("Not found\n");
                    rc = EXIT_SUCCESSFUL;
                }
            }
            break;
        default:
            rc = ERR_ARGS;
            break;
    }
    fclose(file);

    // printf("Rc = %d\n", rc);
    return rc;
}

