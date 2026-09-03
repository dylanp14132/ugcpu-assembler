# Micro-Gator CPU Assembler

A simple assembler for a custom 8-bit CPU made for a DE-10 Lite for my digital logic class. Assembles plain-text source into either a Quartus Memory Initialization File (`.mif`) compatible format or raw hex output.

## Usage

```bash
./ugcpu_assembler <input_file> <output_file> [flags]
```

The `input_file` and `output_file` arguments are required. All subsequent flags are optional and order-independent.

**Flags:**

| Flag | Effect |
|---|---|
| `--nc` | No comments — _omit the original source line as a trailing comment in the output_ |
| `--raw` | Raw output — _write plain hex digits only instead of a full Quartus `.mif` file_ |

**Examples:**

```bash
# Full .mif file with source comments
./ugcpu_assembler sample.asm program.mif

# .mif file, no comments
./ugcpu_assembler sample.asm program.mif --nc

# Raw hex only, no comments, no .mif header/footer
./ugcpu_assembler sample.asm program.hex --raw --nc
```

## Assembly syntax

| Mnemonic | Operand | Description |
|---|---|---|
| `TAB` | None | Copy A to B |
| `ABA` | None | A = A + B + Cin |
| `JMP` `addr` | Address (0–15) | Load PC with the given address |
| `LDAA` `#data` | Immediate (0–15) | Load A with the given data |
| `SAL` | None | Shift A left 1 bit (result in A) |
| `SAR` | None | Shift A right 1 bit (result in A) |

**Notes:**

- Mnemonics are case-insensitive (`ldaa`, `LDAA`, and `LdAa` are all valid).
- Immediates (`LDAA`) must be prefixed with `#`:
    - `LDAA #5` — decimal
    - `LDAA #$0A` — hexadecimal (`$` prefix, after the `#`)
- Addresses (`JMP`) are written without a `#` prefix:
    - `JMP 5` — decimal
    - `JMP $0A` — hexadecimal
- Operand values must fit in 4 bits: 0–15 (`0x0`–`0xF`). Out-of-range values are rejected.
- Instructions that take no operand (`TAB`, `ABA`, `SAL`, `SAR`) must not have an operand on these.
- Anything after a `;` on a line is treated as a comment and ignored.