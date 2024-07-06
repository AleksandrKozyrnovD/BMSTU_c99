#include "inputoutput.h"


int get_line(char *buf, size_t buf_size)
{
    char *ptr;
    // printf("Input string: ");
    if (!fgets(buf, buf_size, stdin))
        return ERR_IO;

    if ((strlen(buf) == MAX_STRLEN) && (buf[strlen(buf) - 1] != '\n'))
        return ERR_BUF_TOO_SMALL;

    ptr = strrchr(buf, '\n');
    if (ptr)
    {
        *ptr = 0;
        return OK;
    }
    return ERR_BUF_TOO_SMALL;
}
