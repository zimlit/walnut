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

#include <stdio.h>
#include <walnut/mem.h>

void
walnutMemInit(WalnutMem *mem, size_t len, size_t codeLen)
{
  if (len < codeLen)
    {
      fprintf(
          stderr,
          "ERROR: length must be >= than the length of the text segment\n");
      exit(EXIT_FAILURE);
    }
  mem->data    = malloc(len * 8);
  mem->len     = len;
  mem->codeLen = codeLen;
}

void
walnutMemFree(WalnutMem *mem)
{
  free(mem->data);
  mem->data    = NULL;
  mem->len     = 0;
  mem->codeLen = 0;
}

uint64_t *
walnutMemBrk(WalnutMem *mem, int64_t inc)
{
  if (inc == 0)
    {
      return mem->data + mem->len - 1;
    }
  if (mem->len + inc < mem->codeLen)
    {
      fprintf(stderr, "ERROR: attempted to resize heap to size to small to "
                      "hold text segment\n");
      exit(EXIT_FAILURE);
    }
  mem->data = realloc(mem->data, (mem->len + inc) * 8);
  if (!mem->data)
    {
      fprintf(stderr, "ERROR: out of memory");
      exit(1);
    }

  mem->len += inc;
  return mem->data + mem->len - 1;
}