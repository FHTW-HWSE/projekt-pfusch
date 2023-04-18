#pragma once

#include "base.h"

int get_int_from_user (int *result, char *input, int input_length);

int is_program_termination_requested(char *string);

int get_string_from_user(char *result, int input_length);