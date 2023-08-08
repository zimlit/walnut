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

#define WALNUT_FETCH(walnut) walnut->mem.data[walnut->pc++]
#define WALNUT_OPCODE(instruction) instruction>>56