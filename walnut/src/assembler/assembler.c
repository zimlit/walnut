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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <walnut/assembler/assembler.h>
#include <walnut/opcode.h>

void
walnutAssemblerOutputInit(WalnutAssemblerOutput *output)
{
  output->data = NULL;
  output->cap  = 0;
  output->len  = 0;
}

void
walnutAssemblerOutputPush(WalnutAssemblerOutput *output, uint64_t item)
{
  if (output->len + 1 > output->cap)
    {
      output->cap  = output->cap ? output->cap * 2 : 64;
      output->data = realloc(output->data, output->cap);
    }
  output->data[output->len] = item;
  output->len++;
}

void
walnutAssemblerOutputFree(WalnutAssemblerOutput *output)
{
  free(output->data);
  walnutAssemblerOutputInit(output);
}

// TODO: error handling
WalnutAssemblerOutput
walnutAssemble(const char *source)
{
  WalnutAssemblerOutput output;
  walnutAssemblerOutputInit(&output);

  int i = 0;
  while (source[i] != '\0')
    {
      switch (source[i])
        {
        case 'l':
          {
            switch (source[i + 1])
              {
              case 'd':
                {
                  switch (source[i + 2])
                    {
                    case 'i':
                      {
                        uint64_t instr = (uint64_t)WalnutOpLdi << 56;
                        i += 3;
                        while (isspace(source[i]))
                          {
                            i++;
                          }
                        i++;
                        char *end;
                        uint8_t reg = strtoul(source + i, &end, 10);
                        instr |= (uint64_t)reg << 48;
                        i = end - source + 1;

                        while (isspace(source[i]))
                          {
                            i++;
                          }
                        uint32_t val = strtoul(source + i, &end, 10);
                        instr |= (uint64_t)val << 16;
                        i = end - source;
                        walnutAssemblerOutputPush(&output, instr);
                        break;
                      }
                    }
                  break;
                }
              }
            break;
          }
        default:
          i++;
          break;
        }
    }

  return output;
}