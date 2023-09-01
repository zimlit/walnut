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

typedef enum
{
  WALNUT_TOKEN_HLT,
  WALNUT_TOKEN_LDI,

  WALNUT_TOKEN_REG,
  WALNUT_TOKEN_NUMBER,
  WALNUT_TOKEN_COMMA,
  WALNUT_TOKEN_IDENTIFIER,

  WALNUT_TOKEN_ERROR,
  WALNUT_TOKEN_EOF,
} WalnutTokenType;

typedef struct
{
  WalnutTokenType type;
  int line;
  int col;
  char *start;
  int length;
} WalnutToken;

typedef struct
{
  int line;
  int col;
  int pos;
  char *source;
} WalnutLexer;

void walnutInitLexer(WalnutLexer *lexer, char *source);
WalnutToken walnutLexToken(WalnutLexer *lexer);
