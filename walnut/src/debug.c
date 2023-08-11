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
        printf("%04x\t", i);
        switch (WALNUT_OPCODE(code[i])) {
            case WalnutOpHlt:
                printf("hlt\n");
                break;
            case WalnutOpLdi: {
                uint8_t reg = WALNUT_FIRST_PARAM(code[i]);
                uint64_t val = WALNUT_IMMEDIATE(code[i]);
                printf("ldi %u, %llu\n", reg, val);
                break;
            }
            case WalnutOpLdm: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t off = WALNUT_SECOND_PARAM(code[i]);
                printf("ldm %u, %u\n", dest, off);
                break;
            }
            case WalnutOpLda: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t addr = WALNUT_SECOND_PARAM(code[i]);
                printf("lda %u, %u\n", dest, addr);
                break;
            }
            case WalnutOpLdr: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t src = WALNUT_SECOND_PARAM(code[i]);
                printf("ldr %d, %d\n", dest, src);
                break;
            }
            case WalnutOpSto: {
                uint8_t off = WALNUT_FIRST_PARAM(code[i]);
                uint8_t src = WALNUT_SECOND_PARAM(code[i]);
                printf("sto %d, %d\n", off, src);
                break;
            }
            case WalnutOpSta: {
                uint8_t addr = WALNUT_FIRST_PARAM(code[i]);
                uint8_t src = WALNUT_SECOND_PARAM(code[i]);
                printf("sta %d, %d\n", addr, src);
                break;
            }
            case WalnutOpAdd: {
                uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
                uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
                printf("add %u, %u, %u\n", reg1, reg2, reg3);
                break;
            }
            case WalnutOpSub: {
                uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
                uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
                printf("sub %u, %u, %u\n", reg1, reg2, reg3);
                break;
            }
            case WalnutOpMul: {
                uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
                uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
                printf("mul %u, %u, %u\n", reg1, reg2, reg3);
                break;
            }
            case WalnutOpDiv: {
                uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
                uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
                printf("div %u, %u, %u\n", reg1, reg2, reg3);
                break;
            }
            case WalnutOpMod: {
                uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
                uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
                printf("mod %u, %u, %u\n", reg1, reg2, reg3);
                break;
            }
            case WalnutOpLbs: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t src = WALNUT_SECOND_PARAM(code[i]);
                uint8_t amm = WALNUT_THIRD_PARAM(code[i]);
                printf("lbs %d, %d, %d\n", dest, src, amm);
                break;
            }
            case WalnutOpRbs: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t src = WALNUT_SECOND_PARAM(code[i]);
                uint8_t amm = WALNUT_THIRD_PARAM(code[i]);
                printf("rbs %d, %d, %d\n", dest, src, amm);
                break;
            }
            case WalnutOpAnd: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t op1 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t op2 = WALNUT_THIRD_PARAM(code[i]);
                printf("and %d, %d, %d\n", dest, op1, op2);
                break;
            }
            case WalnutOpBor: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t op1 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t op2 = WALNUT_THIRD_PARAM(code[i]);
                printf("bor %d, %d, %d\n", dest, op1, op2);
                break;
            }
            case WalnutOpXor: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t op1 = WALNUT_SECOND_PARAM(code[i]);
                uint8_t op2 = WALNUT_THIRD_PARAM(code[i]);
                printf("xor %d, %d, %d\n", dest, op1, op2);
                break;
            }
            case WalnutOpNot: {
                uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
                uint8_t op1 = WALNUT_SECOND_PARAM(code[i]);
                printf("not %d, %d\n", dest, op1);
                break;
            }
            case WalnutOpJmp: {
                uint8_t addr = WALNUT_FIRST_PARAM(code[i]);
                printf("jmp %d\n", addr);
                break;
            }
        }
    }
}

void walnutDumpRegisterFile(Walnut *walnut) {
    printf("Register file {\n");
    for (int wp = 0; wp < 16; wp++) {
        printf("\tWindow %2d {", wp);
        for (int i = 0; i < 16; i++) {
            printf("r%d: %llX", i, walnut->registers[i+wp*16]);
            if (i != 15)
                printf(", ");
        }
        printf("}\n");
    }
    printf("}\n");
}