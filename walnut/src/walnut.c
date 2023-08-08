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

#include <walnut/walnut.h>
#include <string.h>

void walnutInit(Walnut *walnut, uint64_t *code, size_t codeLen) {
    walnutMemInit(&walnut->mem, codeLen);
    walnut->pc = 0;
    memset(walnut->registers, 0, 128*8);
    walnut->wp = 0;
    walnut->flags = 0;
}

void walnutFree(Walnut *walnut) {
    walnutMemFree(&walnut->mem);
    walnut->pc = 0;
    memset(walnut->registers, 0, 128*8);
    walnut->wp = 0;
    walnut->flags = 0;
}