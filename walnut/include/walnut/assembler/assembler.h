// Copyright (C) 2023 Devin Rockwell
//
// walnut is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// walnut is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with walnut. If not, see <http://www.gnu.org/licenses/>.

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct
{
  uint64_t *data;
  size_t len;
  size_t cap;
  bool hadError;
} WalnutAssemblerOutput;

void walnutAssemblerOutputFree(WalnutAssemblerOutput *output);

WalnutAssemblerOutput walnutAssemble(char *source);