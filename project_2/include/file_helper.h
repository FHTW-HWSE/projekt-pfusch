#pragma once

#include "base.h"

_result_t
read_lines_from_file (char *file_path, char ***lines, size_t *line_count);

_result_t
write_to_file(char *path, char *string);

_result_t
read_from_file (char *file_path, char **line);
