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

#ifndef WALNUT_DECODE_H
#define WALNUT_DECODE_H

#define WALNUT_FETCH(walnut)             walnut->mem.data[walnut->pc++]
#define WALNUT_OPCODE(instruction)       instruction >> 56
#define WALNUT_FIRST_PARAM(instruction)  (instruction << 8) >> 56
#define WALNUT_SECOND_PARAM(instruction) (instruction << 16) >> 56
#define WALNUT_THIRD_PARAM(instruction)  (instruction << 24) >> 56
#define WALNUT_IMMEDIATE(instruction)    (instruction << 16) >> 32
#define WALNUT_GET_REG(walnut, reg)      walnut->registers[reg + (walnut->wp * 16)]

#endif