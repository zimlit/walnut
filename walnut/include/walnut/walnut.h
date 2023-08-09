// Copyright (C) 2023 Devin Rockwell
// 
// This file is part of walnut.
// 
// walnut is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// walnut is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with walnut.  If not, see <http://www.gnu.org/licenses/>.

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mem.h"
#include "opcode.h"

#ifndef WALNUT_H
#define WALNUT_H

typedef struct {
    WalnutMem mem;
    size_t pc;
    uint64_t registers[256];
    uint8_t wp;
    uint16_t flags;
    bool running;  
} Walnut;

void walnutInit(Walnut *walnut, uint64_t *code, size_t codeLen);
void walnutFree(Walnut *walnut);

void walnutRun(Walnut *walnut);
#endif