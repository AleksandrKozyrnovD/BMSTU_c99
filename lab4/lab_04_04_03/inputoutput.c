#include "inputoutput.h"

int get_line(char *buf, size_t buf_size)
{
    char *ptr;
    if (!fgets(buf, buf_size, stdin))
        return ERR_IO;

    ptr = strrchr(buf, '\n');
    if (ptr)
    {
        *ptr = 0;
        return OK;
    }
    return ERR_BUF_TOO_SMALL;
}
