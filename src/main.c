#include <stdio.h>
#include <string.h>
#include "parser.h"

#define START_ADDR 0x47A0

int main(const int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    uint8_t flag_bits = 0;
    for (size_t i = 3; i < argc; ++i) {
        if (strcasecmp(argv[i], "--nc") == 0) {flag_bits = flag_bits | 0x01;}
        else if (strcasecmp(argv[i], "--raw") == 0) {flag_bits = flag_bits | 0x02;}
        else {
            fprintf(stderr, "unknown flag \"%s\"\n", argv[i]);
            return 1;
        }
    }

    FILE* in = fopen(argv[1],"r");
    if (in == NULL) {
        fprintf(stderr, "error opening file\n");
        return 1;
    }

    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "error writing to \"%s\"\n", argv[2]);
        fclose(in);
        return 1;
    }

    if (!(flag_bits & 0x02)) {
        fputs("DEPTH = 32768;	% Address Bus Size %\n"
                "WIDTH = 8;		% Data Format %\n\n"
                "ADDRESS_RADIX = HEX;	% Address Format %\n"
                "DATA_RADIX = HEX;		% Data Format %\n\n"
                "CONTENT\n"
                "BEGIN\n\n\0", out);
        fprintf(out, "[0000..%X]    :    00;\n\n", START_ADDR - 1);
    }

    uint16_t curr_addr = START_ADDR;
    char buf[256] = {0};

    while (fgets(buf, sizeof(buf), in) != NULL) {
        encoded_instruction_t instr;
        uint8_t is_blank;
        if (!assemble_line(buf, &instr, &is_blank)) {
            format_line(buf);
            fprintf(stderr, "error encoding instruction: \"%s\"", buf);
            return 1;
        }
        if (is_blank) {continue;}
        format_line(buf);

        if (flag_bits & 0x02) {fprintf(out, "0%X", instr.word >> 4);}
        else {fprintf(out, "%X            :	 0%X;", curr_addr, instr.word >> 4);}

        if (flag_bits & 0x01) {fprintf(out, "\n");}
        else {fprintf(out, "  -- %s\n", buf);}


        ++curr_addr;
        if (!instr.has_op) {continue;}
        if (flag_bits & 0x02) {fprintf(out, "0%X\n", instr.word & 0x0F);}
        else {fprintf(out, "%X            :	 0%X;\n", curr_addr, instr.word & 0x0F);}
        ++curr_addr;
    }

    if (!(flag_bits & 0x02)) {
        fprintf(out, "\n[%X..7FFF]    :	 00;\n\n", curr_addr);
        fputs("END ;\0", out);
    }

    fclose(in);
    fclose(out);

    printf("Success!\n");
    return 0;
}
