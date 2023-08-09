/**
 * Copyright (C) 2023 Devin Rockwell
 * 
 * This file is part of walnut.
 * 
 * walnut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * walnut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with walnut.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <walnut/debug.h>
#include <walnut/decode.h>
#include <walnut/opcode.h>
#include <stdio.h>

void walnutDisassemble(uint64_t *code, size_t codeLen) {
    for (int i = 0; i < codeLen; i++) {
        printf("%04d\t", i);
        switch (WALNUT_OPCODE(code[i])) {
            case WalnutOpHlt:
                printf("hlt\n");
                break;
            case WalnutOpLdi:
                uint8_t reg = WALNUT_FIRST_PARAM(code[i]);
                uint64_t val = WALNUT_IMMEDIATE(code[i]);
                printf("ldi %u, %llu\n", reg, val);
                break;
            case WalnutOpAdd:
                uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
                uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
                printf("add %u, %u, %u\n", reg1, reg2, reg3);
                break;
        }
    }
}

void walnutDumpRegisterFile(Walnut *walnut) {
    printf("Register file {\n");
    for (int wp = 0; wp < 16; wp++) {
        printf("\tWindow %2d {", wp);
        for (int i = 0; i < 16; i++) {
            printf("r%d: %d", i, walnut->registers[i+wp*16]);
            if (i != 15)
                printf(", ");
        }
        printf("}\n");
    }
    printf("}\n");
}