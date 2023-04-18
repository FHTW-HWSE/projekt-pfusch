#pragma once
#include <stdlib.h>

// stuff for results
enum result_state
{
    R_SUCCESS,
    R_FAILIURE,
    R_ERROR
};

enum result_cust_error
{
    C_R_DEFAULT,
    C_R_NULL_PTR,
    C_R_BUG,
    C_R_FILE_READ,
    C_R_FILE_WRITE
};

typedef union result_value_u
{
    void *result;                      // R_SUCCESS
    enum result_cust_error cust_error; // R_FAILIURE
    int errno_val;                     // R_ERROR
} _result_val_t;

typedef struct result_s
{
    enum result_state state;
    _result_val_t value;
    char *message;
} _result_t;
