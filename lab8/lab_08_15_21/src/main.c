#include "matrix.h"
#include "matrix_alloc.h"
#include "matrix_operations.h"
#include <math.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{
    errors_t rc = EXIT_SUCCESSFUL;

    matrix_t a = { .matrix = NULL, .rows = 0, .cols = 0 };
    matrix_t b = { .matrix = NULL, .rows = 0, .cols = 0 };
    matrix_t result = { .matrix = NULL, .rows = 0, .cols = 0 };
    matrix_t copy = { .matrix = NULL };
    
    if (argc != 5 && argc != 4)
        return ERR_ARGS;
    
    rc = read_matrix_ex(argv[2], &a);
    if (argc == 4 && strcmp(argv[1], "o") == 0 && !rc)
    {
        rc = matrix_alloc(&result, a.rows, a.cols);
        if (a.rows != a.cols)
            rc = ERR_RANGE;
        if (!rc)
        {
            rc = matrix_copy(&a, &copy);
            if (!rc)
            {
                double det = gauss_determinant(&copy);
                // printf("%lf\n", det);
                if (fabs(det) < MACHINE_ZERO)
                    rc = ERR_SINGULAR;

                if (!rc)
                {
                    rc = get_inverse_matrix(&a, &result);
                    if (!rc)
                        rc = print_matrix_ex(argv[3], &result);
                }
            }
        }
    }
    else if (argc == 5 && !rc)
    {
        rc = read_matrix_ex(argv[3], &b);
        if (!rc)
        {
            if (strcmp(argv[1], "a") == 0)
            {
                rc = matrix_alloc(&result, a.rows, a.cols);
                if (!rc)
                {
                    rc = add(&a, &b, &result);
                    if (!rc)
                        print_matrix_ex(argv[4], &result);
                }
            }
            else if (strcmp(argv[1], "m") == 0)
            {
                rc = matrix_alloc(&result, a.rows, b.cols);
                if (!rc)
                {
                    rc = multiply(&a, &b, &result);
                    if (!rc)
                        rc = print_matrix_ex(argv[4], &result);
                }
            }
            else
                rc = ERR_ARGS;
        }
    }
    else if (rc == EXIT_SUCCESSFUL)
        rc = ERR_ARGS;
    
    free_matrix(&a, a.rows);
    free_matrix(&b, b.rows);
    free_matrix(&result, result.rows);
    free_matrix(&copy, copy.rows);

    return rc;
}

