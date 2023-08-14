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

#ifndef WALNUT_DEBUG_H
#define WALNUT_DEBUG_H

#include <inttypes.h>
#include <stddef.h>
#include <walnut/walnut.h>

void walnutDisassemble(uint64_t *code, size_t codeLen);
void walnutDumpRegisterFile(Walnut *walnut);

#endif