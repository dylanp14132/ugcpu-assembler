#include <stdio.h>
#include <stdint.h>

int main(const int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "invalid number of arguments\n");
        return 1;
    }

    FILE *in = fopen(argv[1],"r");

    if (in == NULL) {
        fprintf(stderr, "error opening file\n");
        return 1;
    }

    FILE *out = fopen("rom.mif", "w");

    if (out == NULL) {
        fprintf(stderr, "error writing to rom.mif\n");
        fclose(in);
        return 1;
    }

    fputs("DEPTH = 32768;	% Address Bus Size %\n"
                "WIDTH = 8;		% Data Format %\n\n"
                "ADDRESS_RADIX = HEX;	% Address Format %\n"
                "DATA_RADIX = HEX;		% Data Format %\n\n"
                "CONTENT\n"
                "BEGIN\n\n"
                "[0000..479F]	:	0;\n\n\0",out);

    uint16_t curr_addr = 0x47A0;
    fprintf(out, "[%X..7FFF]	:	0;\n\n", curr_addr);

    fputs("END ;\0", out);

    fclose(out);

    return 0;
}
