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
#include <walnut/debug.h>
#include <stddef.h>
#include <stdio.h>

int main() {
    Walnut walnut;
    uint64_t code[] = {
        0x1000000000A0000,
        0x1010000000A0000,
        0x1300010000000000,
    };
    walnutDisassemble(code, 3);
    walnutInit(&walnut, code, 3);
    walnutRun(&walnut);
    walnutDumpRegisterFile(&walnut);
    printf("%llx\n", walnut.mem.data[0x10]);
    walnutFree(&walnut);
    return 0;
}