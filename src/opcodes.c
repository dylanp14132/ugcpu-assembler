#include <string.h>
#include "opcodes.h"

static const instruction_t isa_table[] = {
    {.mnemonic = "TAB",  .opcode = 0b000, .operand_type = OP_NONE},
    {.mnemonic = "ABA",  .opcode = 0b001, .operand_type = OP_NONE},
    {.mnemonic = "JMP",  .opcode = 0b010, .operand_type = OP_ADDR},
    {.mnemonic = "LDAA", .opcode = 0b011, .operand_type = OP_DATA},
    {.mnemonic = "SAL",  .opcode = 0b100, .operand_type = OP_NONE},
    {.mnemonic = "SAR",  .opcode = 0b101, .operand_type = OP_NONE},
};

const instruction_t* lookup_opcode(const char* mnemonic) {
    for (size_t i = 0; i < sizeof(isa_table) / sizeof(isa_table[0]); ++i) {
        if (strcasecmp(mnemonic, isa_table[i].mnemonic) == 0) {
            return &isa_table[i];
        }
    }
    return NULL;
}