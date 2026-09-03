#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "opcodes.h"

static void strip_comment(const char* line) {
    char* semi = strchr(line, ';');
    if (semi != NULL) {*semi  = '\0';}
}

static void trim(char* str) {
    char* start = str;
    while (isspace((unsigned char)*start)) ++start;
    memmove(str, start, strlen(start) + 1);
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len-1])) {str[--len] = '\0';}
}

static uint8_t parse_number(const char* tok, long* out) {
    if (tok[0] == '#') {++tok;}
    char* endptr;
    long val = 0;
    if (tok[0] == '$') {
        ++tok;
        val = strtol(tok, &endptr, 16);
    } else {val = strtol(tok, &endptr, 10);}
    if (*endptr != 0 || endptr == tok) {return 0;}
    *out = val;
    return 1;
}

void format_line(char* str) {
    strip_comment(str);
    trim(str);
    char* space = str;
    while (!isspace((unsigned char)*space)) ++space;
    ++space;
    if (*space) {trim(space);}
}

uint8_t assemble_line(const char* raw_line, encoded_instruction_t* out, uint8_t* is_blank) {
    *is_blank = 0;
    out->word = 0;
    out->has_op = 0;

    char buffer[128];
    strncpy(buffer, raw_line,sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    strip_comment(buffer);
    trim(buffer);

    if (buffer[0] == '\0') {
        *is_blank = 1;
        return 1;
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
    if (def == NULL) {return 0;}

    uint8_t operand_bits = 0;

    switch (def->operand_type) {
        case OP_NONE:
            if (operand_str[0] != '\0') {return 0;}
            break;
        case OP_DATA:
            if (operand_str[0] == '\0') {return 0;}
            if (operand_str[0] != '#') {return 0;}
        case OP_ADDR:
            if (def->operand_type == OP_ADDR && operand_str[0] == '#') {return 0;}
            long val = 0;
            if (!parse_number(operand_str, &val)) {return 0;}
            if (val < 0 || val > 15) {return 0;}
            operand_bits = (uint8_t)val;
            out->has_op = 1;
            break;
        default:
            break;
    }

    out->word = (uint8_t)((def->opcode << 4) | (operand_bits & 0x0F));
    return 1;
}