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
void trim(char* str) {
    char* start = str;
    while (isspace((unsigned char)*start)) ++start;
    memmove(str, start, strlen(start) + 1);
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len-1])) {str[--len] = '\0';}
}

static bool parse_number(const char* tok, long* out) {
    if (tok[0] == '#') {++tok;}
    char* endptr;
    const long val = strtol(tok, &endptr, 0);
    if (*endptr != 0 || endptr == tok) {return false;}
    *out = val;
    return true;
}

bool assemble_line(const char* raw_line, const uint16_t line_number, encoded_instruction_t* out, bool* is_blank) {
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
    while (*space && !isspace((unsigned char)*space)) {++space;}

    char operand_str[32] = {0};
    if (*space) {
        *space = '\0';
        char* op = space + 1;
        trim(op);
        strncpy(operand_str, op, sizeof(operand_str) - 1);
    }

    const instruction_t* def = lookup_opcode(buffer);
    if (def == NULL) {
        return false;
    }

    uint8_t operand_bits = 0;

    switch (def->operand_type) {
        case OP_NONE:
            if (operand_str[0] != '\0') {return false;}
            break;
        case OP_ADDR:
        case OP_DATA:
            if (operand_str[0] == '\0') {return false;}
            long val = 0;
            if (!parse_number(operand_str, &val)) {return false;}
            if (val < 0 || val > 31) {return false;}
            operand_bits = (uint8_t)val;
            break;
        default:
            break;
    }

    out->word = (uint8_t)((def->opcode << 5) | (operand_bits & 0x1F)); // TODO: Change last 4 bits to opcode and first 4 to operand

    return true;
}