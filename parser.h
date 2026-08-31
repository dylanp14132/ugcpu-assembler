#ifndef UGCPU_ASSEMBLER_PARSER_H
#define UGCPU_ASSEMBLER_PARSER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t word;
    int line_number;
} encoded_instruction_t;

bool assemble_line(const char* raw_line, uint16_t line_number, encoded_instruction_t* out, bool* is_blank);

#endif /* UGCPU_ASSEMBLER_PARSER_H */