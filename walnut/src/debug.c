/**
 * Copyright (C) 2023 Devin Rockwell
 *
 * walnut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * walnut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WArANTY; without even the implied waranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with walnut. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <walnut/debug.h>
#include <walnut/decode.h>
#include <walnut/opcode.h>

void
walnutDisassemble(uint64_t *code, size_t codeLen)
{
  for (size_t i = 0; i < codeLen; i++)
    {
      printf("%04lx\t", i);
      switch (WALNUT_OPCODE(code[i]))
        {
        case WalnutOpHlt:
          printf("hlt\n");
          break;
        case WalnutOpLdi:
          {
            uint8_t reg  = WALNUT_FIRST_PARAM(code[i]);
            uint64_t val = WALNUT_IMMEDIATE(code[i]);
            printf("ldi r%u, %" PRIu64 "\n", reg, val);
            break;
          }
        case WalnutOpLda:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
            uint8_t addr = WALNUT_SECOND_PARAM(code[i]);
            printf("lda r%u, r%u\n", dest, addr);
            break;
          }
        case WalnutOpLdr:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
            uint8_t src  = WALNUT_SECOND_PARAM(code[i]);
            printf("ldr r%u, r%u\n", dest, src);
            break;
          }
        case WalnutOpSto:
          {
            uint8_t off = WALNUT_FIRST_PARAM(code[i]);
            uint8_t src = WALNUT_SECOND_PARAM(code[i]);
            printf("sto r%u, r%u\n", off, src);
            break;
          }
        case WalnutOpAdd:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
            uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
            uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
            printf("add r%u, r%u, r%u\n", reg1, reg2, reg3);
            break;
          }
        case WalnutOpSub:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
            uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
            uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
            printf("sub r%u, r%u, r%u\n", reg1, reg2, reg3);
            break;
          }
        case WalnutOpMul:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
            uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
            uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
            printf("mul r%u, r%u, r%u\n", reg1, reg2, reg3);
            break;
          }
        case WalnutOpDiv:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
            uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
            uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
            printf("div r%u, r%u, r%u\n", reg1, reg2, reg3);
            break;
          }
        case WalnutOpMod:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(code[i]);
            uint8_t reg2 = WALNUT_SECOND_PARAM(code[i]);
            uint8_t reg3 = WALNUT_THIRD_PARAM(code[i]);
            printf("mod r%u, r%u, r%u\n", reg1, reg2, reg3);
            break;
          }
        case WalnutOpLbs:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
            uint8_t src  = WALNUT_SECOND_PARAM(code[i]);
            uint8_t amm  = WALNUT_THIRD_PARAM(code[i]);
            printf("lbs r%u, r%u, r%u\n", dest, src, amm);
            break;
          }
        case WalnutOpRbs:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
            uint8_t src  = WALNUT_SECOND_PARAM(code[i]);
            uint8_t amm  = WALNUT_THIRD_PARAM(code[i]);
            printf("rbs r%u, r%u, r%u\n", dest, src, amm);
            break;
          }
        case WalnutOpAnd:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
            uint8_t op1  = WALNUT_SECOND_PARAM(code[i]);
            uint8_t op2  = WALNUT_THIRD_PARAM(code[i]);
            printf("and r%u, r%u, r%u\n", dest, op1, op2);
            break;
          }
        case WalnutOpBor:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
            uint8_t op1  = WALNUT_SECOND_PARAM(code[i]);
            uint8_t op2  = WALNUT_THIRD_PARAM(code[i]);
            printf("bor r%u, r%u, r%u\n", dest, op1, op2);
            break;
          }
        case WalnutOpXor:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
            uint8_t op1  = WALNUT_SECOND_PARAM(code[i]);
            uint8_t op2  = WALNUT_THIRD_PARAM(code[i]);
            printf("xor r%u, r%u, r%u\n", dest, op1, op2);
            break;
          }
        case WalnutOpNot:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(code[i]);
            uint8_t op1  = WALNUT_SECOND_PARAM(code[i]);
            printf("not r%u, r%u\n", dest, op1);
            break;
          }
        case WalnutOpJmp:
          {
            uint8_t addr = WALNUT_FIRST_PARAM(code[i]);
            printf("jmp r%u\n", addr);
            break;
          }
        case WalnutOpCmp:
          {
            uint8_t op1 = WALNUT_FIRST_PARAM(code[i]);
            uint8_t op2 = WALNUT_SECOND_PARAM(code[i]);
            printf("cmp r%u, r%u\n", op1, op2);
            break;
          }
        }
    }
}

void
walnutDumpRegisterFile(Walnut *walnut)
{
  printf("Register file {\n");
  for (int wp = 0; wp < 16; wp++)
    {
      printf("\tWindow %2d {", wp);
      for (int i = 0; i < 16; i++)
        {
          printf("r%u: %" PRIu64, i, walnut->registers[i + wp * 16]);
          if (i != 15)
            printf(", ");
        }
      printf("}\n");
    }
  printf("}\n");
  printf("Flags: %u\n", walnut->flags);
}