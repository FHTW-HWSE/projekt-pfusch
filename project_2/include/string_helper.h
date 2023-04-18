#pragma once

#include "base.h"

int
strcmp_i (const char *a, const char *b);

_result_t
get_substrings_by_delimiter (
    const char *string,
    const char *delimiters,
    char ***substrings,
    size_t *substring_count);

void
dispose_lines (char **lines, size_t line_count);

int
find_substring (
    const char *string,
    const size_t substring_count,
    char *substrings[],
    const char *delimiters,
    size_t *start_index,
    size_t *end_index);

_result_t
write_char_to_line (
    char **line,
    size_t *length,
    size_t *index,
    char c);

int
charcmp_i(char a, char b);