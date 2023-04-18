#include "base.h"
#include "structs.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief prints result message to stdout.
 * @param r 
 */
void
print_result (_result_t r)
{
    switch (r.state)
    {
    case R_FAILIURE:
        // TODO: create some standard error message
        if (r.message != NULL)
        {
            printf (r.message);
        }
        break;
    case R_ERROR:
        printf ("%s\n", strerror (r.value.errno_val));
    default:
        break;
    }
}

/**
 * @brief prints result to stdout and disposes message.
 * @param r 
 */
void
print_and_dispose_result (_result_t r)
{
    switch (r.state)
    {
    case R_FAILIURE:
        // TODO: create some standard error message
        if (r.message != NULL)
        {
            printf (r.message);
        }
        break;
    case R_ERROR:
        printf ("%s\n", strerror (r.value.errno_val));
    default:
        break;
    }

    dispose_result (r);
}
