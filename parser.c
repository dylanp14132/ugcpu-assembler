#include "parser.h"
#include "opcodes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Remove everything past the ';' */
static void strip_comment(const char* line) {
    char* semi = strchr(line, ';');
    if (semi != NULL) {*semi  = '\0';}
}

/* Remove trailing/leading whitespace */
static void trim(char* str) {
    char* start = str;
    while (isspace((unsigned char)*start)) start++;
    memmove(str, start, strlen(start) + 1);
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len-1])) {str[--len] = '\0';}
}

bool assemble_line(const char* raw_line, const uint16_t line_number, encoded_instruction_t* out, bool* is_blank, char* error, size_t error_length) {
    *is_blank = false;
    out->line_number = line_number;
    out->word = 0;

    char buffer[128];
    strncpy(buffer, raw_line,sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    strip_comment(buffer);
    trim(buffer);

    if (buffer[0] == '\0') {
        *is_blank = true;
        return true;
    }

    char* space = buffer;
    while (*space && !isspace((unsigned char)*space)) {space++;}

    char operand_str[32] = {0};
    if (*space) {
        *space = '\0';
        char* op = space + 1;
        trim(op);
        strncpy(operand_str, op, sizeof(operand_str) - 1);
    }

    return false;
}