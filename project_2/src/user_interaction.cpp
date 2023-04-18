#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base.h"

static const char *const EXIT_REQUEST = "EXIT";

static int read_chars(char *input, int length);
static int is_terminating_char(int c);

/**
 * @brief prompts user to input an int and validates the input. The input gets written into *input.
 * @param result 
 * @param input 
 * @param input_length 
 * @return If the input is an integer returns 1, else 0.
 */
int get_int_from_user(int *result, char *input, int input_length){
    if(result == NULL || input_length <= 0){
        return 0;
    }

    if(!read_chars(input, input_length)){
        return 0;
    }
    
    char *end;
    *result = strtol(input, &end, 10);
    return input != end;
}

/**
 * @brief prompts user to input a string and writes the result into *result.
 * @param result 
 * @param input_length 
 * @return 
 */
int get_string_from_user(char *result, int input_length){
    if(result == NULL || input_length <= 0){
        return 0;
    }
    return read_chars(result, input_length);
}

/**
 * @brief returns 1 if the string equals the termination value.
 * @param string 
 * @return 
 */
int is_program_termination_requested(char *string){
    return !strcmp(string, EXIT_REQUEST);
}

/**
 * @brief reads chars from stdin and puts the found values into *input
 * @param input 
 * @param length 
 * @return returns 1 if read worked, else 0.
 */
static int read_chars(char *input, int length){
    int c = 'a';
    int i = 0;

    for(; i < (length -2) && !is_terminating_char(c); i++){
        c = fgetc(stdin);

        if(ferror(stdin) || c == -1){
            return 0;
        }

        input[i] = c;
    }
    
    input[i-1] = '\0';

    //flush stdin
    while (!is_terminating_char(c))
    {
        c = fgetc(stdin);
    }
    
    return 1;
}

/**
 * @brief checks if c is a terminating value
 * @param c 
 * @return 
 */
static int is_terminating_char(int c){
    return c == '\0' || c == '\n' || c == EOF || feof(stdin);
}
