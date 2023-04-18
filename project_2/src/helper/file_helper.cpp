#include "base.h"
#include "structs.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_helper.h"

static const size_t BUFFER_SEGMENT_SIZE = 100;

/**
 * @brief reads from file and puts contents into param line using malloc.
 * @param file_path 
 * @param line 
 * @return 
 */
_result_t
read_from_file (char *file_path, char **line){
    if(file_path == NULL || line == NULL){
        return create_failure_result("parameter filepath or line is NULL.\n", C_R_NULL_PTR);
    }
    FILE *file = fopen (file_path, "r");

    if (file == NULL)
    {
        return create_error_result ("file can't be opened.\n", EBADF);
    }

    char c;
    size_t buffer_size = BUFFER_SEGMENT_SIZE;
    size_t buffer_index = 0;

    _result_t r_line = r_malloc (buffer_size * sizeof (char));
    if (r_line.state != R_SUCCESS)
    {
        return r_line;
    }

    char *buffer = (char*)r_line.value.result;

    while ((c = fgetc (file)) != EOF && !feof (file))
    {
        if (ferror (file))
        {
            fclose(file);
            return create_failure_result ("error while reading the file.\n", C_R_FILE_READ);
        }

        write_char_to_line (&buffer, &buffer_size, &buffer_index, c);
    }

    write_char_to_line (&buffer, &buffer_size, &buffer_index, '\0');

    size_t length = strlen(buffer);
    *line = (char*)malloc(length * sizeof(char));
    *line = strcpy(*line, buffer);

    free(buffer);
    fclose(file);
    return create_result();
}

/**
 * @brief reads from file and writes lines seperatly into param lines using malloc
 * @param file_path 
 * @param lines 
 * @param line_count 
 * @return 
 */
_result_t
read_lines_from_file (char *file_path, char ***lines, size_t *line_count)
{
    if(file_path == NULL || lines == NULL || line_count == NULL){
        return create_failure_result("one of the provided parameters is NULL.\n", C_R_FILE_READ);
    }

    FILE *file = fopen (file_path, "r");

    if (file == NULL)
    {
        return create_error_result ("file can't be opened.\n", EBADF);
    }

    char c;
    size_t buffer_size = BUFFER_SEGMENT_SIZE;
    size_t buffer_index = 0;

    _result_t r_line = r_malloc (buffer_size * sizeof (char));
    if (r_line.state != R_SUCCESS)
    {
        fclose(file);
        return r_line;
    }

    char *buffer = (char*)r_line.value.result;

    while ((c = fgetc (file)) != EOF && !feof (file))
    {
        if (ferror (file))
        {
            fclose(file);
            free(buffer);
            return create_failure_result ("error while reading the file.\n", C_R_FILE_READ);
        }

        _result_t r_c = write_char_to_line (&buffer, &buffer_size, &buffer_index, c);
        if(r_c.state != R_SUCCESS){
            fclose(file);
            free(buffer);
            return r_c;
        }
    }

    fclose(file);
    _result_t r_sub_str = get_substrings_by_delimiter (buffer, "\n", lines, line_count);
    free(buffer);
    return r_sub_str;
}

/**
 * @brief writes string to file
 * @param path 
 * @param string 
 * @return 
 */
_result_t
write_to_file(char *path, char *string){
    if(path == NULL || string == NULL){
        return create_failure_result("one of the provided parameters is NULL.\n", C_R_FILE_WRITE);
    }

    FILE *file = fopen(path, "w");

    if(file == NULL){
        return create_error_result ("file can't be opened.\n", EBADF);
    }

    int result = fprintf(file, "%s", string);
    fclose(file);
    if(result < 0){
        return create_error_result("there was an error while writing.\n", EIO);
    }

    return create_result();
}
