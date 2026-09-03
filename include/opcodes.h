#ifndef UGCPU_ASSEMBLER_OPCODES_H
#define UGCPU_ASSEMBLER_OPCODES_H

#include <stdint.h>

typedef enum {
    OP_NONE,
    OP_ADDR,
    OP_DATA,
} operand_t;

typedef struct {
    const char *mnemonic;
    uint8_t opcode;
    operand_t operand_type;
} instruction_t;

const instruction_t* lookup_opcode(const char* mnemonic);

#endif /* UGCPU_ASSEMBLER_OPCODES_H */