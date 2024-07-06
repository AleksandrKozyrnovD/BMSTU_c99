#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "readstr.h"
#include "list.h"
#include "node.h"

int main(void)
{
    node_t *head1 = NULL;
    node_t *head2 = NULL;
    char command[16]; //Вводная команда
    errors_t rc = EXIT_SUCCESSFUL;
    size_t pos = 0;
    size_t len = 0;

    if (!fgets(command, sizeof(command), stdin))
        return ERR_IO;
    len = strlen(command);
    if (command[len - 1] == '\n')
        command[--len] = 0;
    if (len != 3)
        return ERR_IO;

    // fgets(tmp, sizeof(tmp), stdin);
    if (!rc)
    {
        if (strcmp(command, "out") == 0)
        {
            rc = readstr(stdin, &head1);
            if (!rc)
            {
                reduce_char(head1, ' ');
                // compact(head1);
            }
        }
        else if (strcmp(command, "sps") == 0)
        {
            rc = readstr(stdin, &head1);
            if (!rc)
            {
                reduce_char(head1, ' ');
                // compact(head1);
            }
        }
        else if (strcmp(command, "cat") == 0)
        {
            rc = readstr(stdin, &head1);
            if (!rc)
            {
                rc = readstr(stdin, &head2);
                if (!rc)
                {
                    concat_str(&head1, &head2);
                    reduce_char(head1, ' ');
                    // compact(head1);
                }
            }
        }
        else if (strcmp(command, "pos") == 0)
        {
            rc = readstr(stdin, &head1);
            if (!rc)
            {
                rc = readstr(stdin, &head2);
                if (!rc)
                {
                    rc = find_str(head1, head2, &pos);
                    if (!rc)
                        printf("%zu\n", pos);
                    else
                    {
                        rc = EXIT_SUCCESSFUL;
                        printf("%d\n", -1);
                    }
                }
            }
        }
        else
            rc = ERR_ARGS;
    }

    if (!rc && strcmp(command, "pos"))
        list_print(stdout, head1);
    list_free(head1);
    list_free(head2);

    return rc;
}

