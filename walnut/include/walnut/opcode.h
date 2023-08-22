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

#ifndef WALNUT_OPCODE_H
#define WALNUT_OPCODE_H

typedef enum
{
  WalnutOpHlt,

  // LOADS
  WalnutOpLdi,
  WalnutOpLda,
  WalnutOpLdr,

  // STORES
  WalnutOpSto,

  // MATH
  WalnutOpAdd,
  WalnutOpSub,
  WalnutOpMul,
  WalnutOpDiv,
  WalnutOpMod,

  // BITWISE
  WalnutOpLbs,
  WalnutOpRbs,
  WalnutOpAnd,
  WalnutOpBor,
  WalnutOpXor,
  WalnutOpNot,

  // JUMPS
  WalnutOpJmp,
  WalnutOpJeq,
  WalnutOpJne,
  WalnutOpJgt,
  WalnutOpJlt,
  WalnutOpJge,
  WalnutOpJle,

  WalnutOpCmp,

  // MEMORY
  WalnutOpBrk,

  // WINDOW MANIPULATION
  WalnutOpIwp,
  WalnutOpDwp,
} WalnutOpcode;

#endif