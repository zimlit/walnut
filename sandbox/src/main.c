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

int main() {
    Walnut walnut;
    uint64_t code[] = {
        0x200030000000000, 
        0x101000000380000, 
        0x602000100000000,
        0,
    };
    walnutDisassemble(code, 4);
    walnutInit(&walnut, code, 4);
    walnutRun(&walnut);
    walnutDumpRegisterFile(&walnut);
    walnutFree(&walnut);
    return 0;
}