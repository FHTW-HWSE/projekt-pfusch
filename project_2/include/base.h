#pragma once
#include "structs.h"
#include <stdlib.h>

_result_t r_malloc (size_t size);

_result_t create_result ();

_result_t
create_failure_result (char *message, enum result_cust_error c);

void
dispose_result (_result_t r);

_result_t
create_error_result (char *message, int error);

_result_t
r_realloc (void *ptr, size_t size);
