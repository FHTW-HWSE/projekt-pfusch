#include "structs.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

_result_t
r_malloc (size_t size);

_result_t
r_realloc (void *ptr, size_t size);

_result_t
create_result ()
{
    _result_t r = { .state = R_SUCCESS, .value.result = NULL };
    return r;
}

/**
 * @brief creates a failure result and sets the message using malloc
 * @param message 
 * @param  
 * @return 
 */
_result_t
create_failure_result (char *message, enum result_cust_error c)
{
    _result_t r = r_malloc (strlen (message) * sizeof(char) + 1);
    if (r.state != R_SUCCESS)
    {
        return r;
    }

    char *m = r.value.result;
    m = strcpy (m, message);


    _result_t out = {
        .state = R_FAILIURE,
        .value.cust_error = c,
        .message = m
    };

    return out;
}

/**
 * @brief creates a failure result and sets the message using malloc
 * @param message 
 * @param error 
 * @return 
 */
_result_t
create_error_result (char *message, int error)
{
    _result_t r = r_malloc (strlen (message) * sizeof(char) + 1);
    if (r.state != R_SUCCESS)
    {
        return r;
    }

    char *m = r.value.result;
    m = strcpy (m, message);

    _result_t out = {
        .state = R_ERROR,
        .value.errno_val = error,
        .message = m
    };

    return out;
}

/**
 * @brief frees the message if set
 * @param r 
 */
void
dispose_result (_result_t r)
{
    switch (r.state)
    {
    case R_FAILIURE:
        if (r.message != NULL)
        {
            free (r.message);
        }
        break;
    case R_ERROR:
        if (r.message != NULL)
        {
            free (r.message);
        }
    default:
        break;
    }
}

/**
 * @brief malloc given size
 * @param size 
 * @return malloc pointer is in .value.result. error result if malloc pointer is NULL but size was greater than 0
 */
_result_t
r_malloc (size_t size)
{

    void *result = malloc (size);

    // result can be null if size is 0 (valid)
    if (result == NULL && size > 0)
    {
        return create_error_result ("cannot allocate memory.\n", ENOMEM);
    }

    _result_t out = create_result ();
    out.value.result = result;

    return out;
}

/**
 * @brief realloc ptr with given size
 * @param ptr 
 * @param size 
 * @return malloc pointer is in .value.result. error result if malloc pointer is NULL but size was greater than 0
 */
_result_t
r_realloc (void *ptr, size_t size)
{
    void *result = realloc (ptr, size);

    if (result == NULL && size > 0)
    {
        return create_error_result ("cannot allocate memory.\n", ENOMEM);
    }

    _result_t out = create_result ();
    out.value.result = result;
    return out;
}
