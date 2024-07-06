#include "logic.h"
#include "inputoutput.h"

int main(void)
{
    char buffer[MAX_STRLEN];
    int return_code;

    return_code = get_line(buffer, MAX_STRLEN);
    switch (return_code)
    {
        case OK:
            break;
        default:
            return return_code;
    }

    
    if (is_number(buffer, strlen(buffer)))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }

    return OK;
}