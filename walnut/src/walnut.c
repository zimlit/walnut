/**
 * Copyright (C) 2023 Devin Rockwell
 *
 * walnut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * walnut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with walnut. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <walnut/decode.h>
#include <walnut/walnut.h>

void
walnutInit(Walnut *walnut, uint64_t *code, size_t codeLen)
{
  walnutMemInit(&walnut->mem, codeLen + 1024 / 8, codeLen);
  memcpy(walnut->mem.data, code, codeLen * 8);
  walnut->pc = 0;
  memset(walnut->registers, 0, 256 * 8);
  walnut->wp      = 0;
  walnut->flags   = 0;
  walnut->running = false;
}

void
walnutFree(Walnut *walnut)
{
  walnutMemFree(&walnut->mem);
  walnut->pc = 0;
  memset(walnut->registers, 0, 256 * 8);
  walnut->wp    = 0;
  walnut->flags = 0;
}

void
walnutRun(Walnut *walnut)
{
  walnut->running = true;

  while (walnut->running)
    {
      uint64_t instruction = WALNUT_FETCH(walnut);
      switch (WALNUT_OPCODE(instruction))
        {
        case WalnutOpHlt:
          walnut->running = false;
          break;
        case WalnutOpLdi:
          {
            uint8_t reg                 = WALNUT_FIRST_PARAM(instruction);
            uint64_t val                = WALNUT_IMMEDIATE(instruction);
            WALNUT_GET_REG(walnut, reg) = val;
            break;
          }
        case WalnutOpLda:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(instruction);
            uint8_t addr = WALNUT_SECOND_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest)
                = walnut->mem.data[WALNUT_GET_REG(walnut, addr)];
            break;
          }
        case WalnutOpLdr:
          {
            uint8_t dest                 = WALNUT_FIRST_PARAM(instruction);
            uint8_t src                  = WALNUT_SECOND_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest) = WALNUT_GET_REG(walnut, src);
            break;
          }
        case WalnutOpSto:
          {
            uint8_t off = WALNUT_FIRST_PARAM(instruction);
            uint8_t src = WALNUT_SECOND_PARAM(instruction);
            walnut->mem.data[walnut->pc + WALNUT_GET_REG(walnut, off)]
                = WALNUT_GET_REG(walnut, src);
            break;
          }
        case WalnutOpAdd:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(instruction);
            uint8_t reg2 = WALNUT_SECOND_PARAM(instruction);
            uint8_t reg3 = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, reg1)
                = WALNUT_GET_REG(walnut, reg2) + WALNUT_GET_REG(walnut, reg3);
            break;
          }
        case WalnutOpSub:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(instruction);
            uint8_t reg2 = WALNUT_SECOND_PARAM(instruction);
            uint8_t reg3 = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, reg1)
                = WALNUT_GET_REG(walnut, reg2) - WALNUT_GET_REG(walnut, reg3);
            break;
          }
        case WalnutOpMul:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(instruction);
            uint8_t reg2 = WALNUT_SECOND_PARAM(instruction);
            uint8_t reg3 = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, reg1)
                = WALNUT_GET_REG(walnut, reg2) * WALNUT_GET_REG(walnut, reg3);
            break;
          }
        case WalnutOpDiv:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(instruction);
            uint8_t reg2 = WALNUT_SECOND_PARAM(instruction);
            uint8_t reg3 = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, reg1)
                = WALNUT_GET_REG(walnut, reg2) / WALNUT_GET_REG(walnut, reg3);
            break;
          }
        case WalnutOpMod:
          {
            uint8_t reg1 = WALNUT_FIRST_PARAM(instruction);
            uint8_t reg2 = WALNUT_SECOND_PARAM(instruction);
            uint8_t reg3 = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, reg1)
                = WALNUT_GET_REG(walnut, reg2) % WALNUT_GET_REG(walnut, reg3);
            break;
          }
        case WalnutOpLbs:
          {
            uint8_t dest                 = WALNUT_FIRST_PARAM(instruction);
            uint8_t src                  = WALNUT_SECOND_PARAM(instruction);
            uint8_t amm                  = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest) = WALNUT_GET_REG(walnut, src)
                                           << WALNUT_GET_REG(walnut, amm);
            break;
          }
        case WalnutOpRbs:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(instruction);
            uint8_t src  = WALNUT_SECOND_PARAM(instruction);
            uint8_t amm  = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest)
                = WALNUT_GET_REG(walnut, src) >> WALNUT_GET_REG(walnut, amm);
            break;
          }
        case WalnutOpAnd:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(instruction);
            uint8_t op1  = WALNUT_SECOND_PARAM(instruction);
            uint8_t op2  = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest)
                = WALNUT_GET_REG(walnut, op1) & WALNUT_GET_REG(walnut, op2);
            break;
          }
        case WalnutOpBor:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(instruction);
            uint8_t op1  = WALNUT_SECOND_PARAM(instruction);
            uint8_t op2  = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest)
                = WALNUT_GET_REG(walnut, op1) | WALNUT_GET_REG(walnut, op2);
            break;
          }
        case WalnutOpXor:
          {
            uint8_t dest = WALNUT_FIRST_PARAM(instruction);
            uint8_t op1  = WALNUT_SECOND_PARAM(instruction);
            uint8_t op2  = WALNUT_THIRD_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest)
                = WALNUT_GET_REG(walnut, op1) ^ WALNUT_GET_REG(walnut, op2);
            break;
          }
        case WalnutOpNot:
          {
            uint8_t dest                 = WALNUT_FIRST_PARAM(instruction);
            uint8_t op1                  = WALNUT_SECOND_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest) = ~WALNUT_GET_REG(walnut, op1);
            break;
          }
        case WalnutOpJmp:
          {
            uint8_t addr = WALNUT_FIRST_PARAM(instruction);
            walnut->pc   = WALNUT_GET_REG(walnut, addr);
            break;
          }
        case WalnutOpJeq:
          {
            switch (walnut->flags)
              {
              case WALNUT_FLAG_EQUAL:
                {
                  uint8_t addr = WALNUT_FIRST_PARAM(instruction);
                  walnut->pc   = WALNUT_GET_REG(walnut, addr);
                  break;
                }
              }
            break;
          }
        case WalnutOpJne:
          {
            if (walnut->flags != WALNUT_FLAG_EQUAL)
              {
                uint8_t addr = WALNUT_FIRST_PARAM(instruction);
                walnut->pc   = WALNUT_GET_REG(walnut, addr);
              }
            break;
          }
        case WalnutOpJgt:
          {
            switch (walnut->flags)
              {
              case WALNUT_FLAG_GREATER:
                {
                  uint8_t addr = WALNUT_FIRST_PARAM(instruction);
                  walnut->pc   = WALNUT_GET_REG(walnut, addr);
                  break;
                }
              }
            break;
          }
        case WalnutOpJlt:
          {
            switch (walnut->flags)
              {
              case WALNUT_FLAG_LESS:
                {
                  uint8_t addr = WALNUT_FIRST_PARAM(instruction);
                  walnut->pc   = WALNUT_GET_REG(walnut, addr);
                  break;
                }
              }
            break;
          }
        case WalnutOpJge:
          {
            switch (walnut->flags)
              {
              case WALNUT_FLAG_GREATER:
              case WALNUT_FLAG_EQUAL:
                {
                  uint8_t addr = WALNUT_FIRST_PARAM(instruction);
                  walnut->pc   = WALNUT_GET_REG(walnut, addr);
                  break;
                }
              }
            break;
          }
        case WalnutOpJle:
          {
            switch (walnut->flags)
              {
              case WALNUT_FLAG_LESS:
              case WALNUT_FLAG_EQUAL:
                {
                  uint8_t addr = WALNUT_FIRST_PARAM(instruction);
                  walnut->pc   = WALNUT_GET_REG(walnut, addr);
                  break;
                }
              }
            break;
          }
        case WalnutOpCmp:
          {
            uint64_t op1
                = WALNUT_GET_REG(walnut, WALNUT_FIRST_PARAM(instruction));
            uint64_t op2
                = WALNUT_GET_REG(walnut, WALNUT_SECOND_PARAM(instruction));
            if (op1 == op2)
              walnut->flags = WALNUT_FLAG_EQUAL;
            else if (op1 < op2)
              walnut->flags = WALNUT_FLAG_LESS;
            else if (op1 > op2)
              walnut->flags = WALNUT_FLAG_GREATER;
            break;
          }
        case WalnutOpBrk:
          {
            uint64_t dest                = WALNUT_FIRST_PARAM(instruction);
            uint64_t inc                 = WALNUT_SECOND_PARAM(instruction);
            WALNUT_GET_REG(walnut, dest) = (uint64_t)walnutMemBrk(
                &walnut->mem, (int64_t)WALNUT_GET_REG(walnut, inc));
            break;
          }
        case WalnutOpIwp:
          {
            walnut->wp++;
            break;
          }
        case WalnutOpDwp:
          {
            walnut->wp--;
            break;
          }
        }
    }
}