#include <stdio.h>

int main() {
    FILE *fptr = fptr = fopen("rom.mif", "w");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fputs("DEPTH = 32768;	% Address Bus Size %\n"
                "WIDTH = 8;		% Data Format %\n\n"
                "ADDRESS_RADIX = HEX;	% Address Format %\n"
                "DATA_RADIX = HEX;		% Data Format %\n\n"
                "CONTENT\n"
                "BEGIN\n\n"
                "[0..479F]	:	0;\n\n\0",fptr);

    unsigned int curr_addr = 0x47A0;
    fprintf(fptr, "[%X..7FFF]	:	0;\n\n", curr_addr);

    fputs("END ;\0", fptr);

    fclose(fptr);

    return 0;
}
