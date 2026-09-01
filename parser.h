#ifndef UGCPU_ASSEMBLER_PARSER_H
#define UGCPU_ASSEMBLER_PARSER_H

#include <stdint.h>

typedef struct {
    uint8_t word;
    uint8_t has_op;
} encoded_instruction_t;

void format_line(char* str);
uint8_t assemble_line(const char* raw_line, encoded_instruction_t* out, uint8_t* is_blank);

#endif /* UGCPU_ASSEMBLER_PARSER_H */