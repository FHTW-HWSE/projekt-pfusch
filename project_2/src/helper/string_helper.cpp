#include <string.h>
#include "base.h"
#include <ctype.h>

static const size_t BUFFER_SEGMENT_SIZE = 100;

/**
 * @brief appends new line using realloc and malloc.
 * @param buffer 
 * @param buffer_length 
 * @param buffer_index 
 * @param substrings 
 * @param substring_count 
 * @return 
 */
static _result_t
create_and_add_new_line 
(
    char *buffer, 
    size_t *buffer_length, 
    size_t *buffer_index, 
    char ***substrings, 
    size_t *substring_count
)
{
    // add new line
    ++(*substring_count);
    _result_t r_ralloc = r_realloc (*substrings, (*substring_count) * sizeof (char **));
    if (r_ralloc.state != R_SUCCESS)
    {
        return r_ralloc;
    }

    *substrings = (char**)r_ralloc.value.result;

    // create line containing the substring
    _result_t r_line = r_malloc (*buffer_index * sizeof (char) + 1);
    if (r_line.state != R_SUCCESS)
    {
        return r_line;
    }

    char *line = (char*)r_line.value.result;
    strcpy (line, buffer);
    (*substrings)[(*substring_count) - 1] = line;

    // reset variables
    *buffer_index = 0;
    memset (buffer, '\0', *buffer_length);

    return create_result ();
}

/**
 * @brief writes char to line. Increases allocaed memory if necessary.
 * @param line 
 * @param length 
 * @param index 
 * @param c 
 * @return 
 */
_result_t
write_char_to_line 
(
    char **line,
    size_t *length,
    size_t *index,
    char c
)
{
    if (*index < ((*length) - 1))
    {
        (*line)[(*index)++] = c;
    }
    else
    {
        *length += BUFFER_SEGMENT_SIZE;
        _result_t r_alloc = r_realloc (*line, (*length) * sizeof (char));
        if (r_alloc.state != R_SUCCESS)
        {
            return r_alloc;
        }

        *line = (char*)r_alloc.value.result;

        memset ((*line) + (*index), '\0', (*length) - (*index));

        (*line)[(*index)++] = c;
    }

    return create_result ();
}

/**
 * @brief frees all lines.
 * @param lines 
 * @param line_count 
 */
void
dispose_lines (char **lines, size_t line_count)
{
    if (lines == NULL)
    {
        return;
    }
    for (size_t i = 0; i < line_count; i++)
    {
        free (lines[i]);
    }
    free (lines);
}

/**
 * @brief findes substrings defined by delimiter and appends those to param substring using realloc.
 * @param string 
 * @param delimiters 
 * @param substrings 
 * @param substring_count 
 * @return 
 */
_result_t
get_substrings_by_delimiter (
    const char *string,
    const char *delimiters,
    char ***substrings,
    size_t *substring_count)
{
    char c;
    char *buffer;
    size_t buffer_length = BUFFER_SEGMENT_SIZE;

    _result_t r_buffer = r_malloc (BUFFER_SEGMENT_SIZE * sizeof (char));
    if (r_buffer.state != R_SUCCESS)
    {
        return r_buffer;
    }

    buffer = (char*)r_buffer.value.result;
    buffer = (char*)memset (buffer, '\0', buffer_length);
    size_t buffer_index = 0;
    size_t read_index = 0;
    while ((c = *(string + read_index)) != '\0')
    {
        if (strchr (delimiters, c) == NULL) // valid character
        {
            _result_t r_wcl = write_char_to_line (&buffer, &buffer_length, &buffer_index, c);
            if (r_wcl.state != R_SUCCESS)
            {
                return r_wcl;
            }
        }
        // found delimiter
        else if (buffer_index != 0) // found a valid substring
        {
            _result_t r_add_line = create_and_add_new_line (buffer, &buffer_length, &buffer_index, substrings, substring_count);
            if (r_add_line.state != R_SUCCESS)
            {
                return r_add_line;
            }
        }
        read_index++;
    }

    // last line
    if (buffer_index > 0)
    {
        _result_t r_add_line = create_and_add_new_line (buffer, &buffer_length, &buffer_index, substrings, substring_count);
        if (r_add_line.state != R_SUCCESS)
        {
            return r_add_line;
        }
    }

    free(buffer);
    return create_result ();
}

/**
 * @brief compares a string case insensitive.
 * @param a 
 * @param b 
 * @return 
 */
int 
strcmp_i(const char *a, const char *b){
    //https://stackoverflow.com/questions/30733786/c99-remove-stricmp-and-strnicmp
    int ca, cb;
    do {
        ca = (unsigned char) *a++;
        cb = (unsigned char) *b++;
        ca = tolower(toupper(ca));
        cb = tolower(toupper(cb));
    } while (ca == cb && ca != '\0');
    return ca - cb;    
}

/**
 * @brief compares a char case insesitive
 * @param a 
 * @param b 
 * @return 
 */
int
charcmp_i(char a, char b){
    //https://stackoverflow.com/questions/30733786/c99-remove-stricmp-and-strnicmp
    int ca, cb;

    ca = (unsigned char) a;
    cb = (unsigned char) b;
    ca = tolower(toupper(ca));
    cb = tolower(toupper(cb));
    
    return ca - cb;    
}
