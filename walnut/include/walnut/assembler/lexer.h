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
#ifndef WALNUT_LEXER_H
#define WALNUT_LEXER_H

typedef enum
{
  WALNUT_TOKEN_HLT,
  WALNUT_TOKEN_LDI,
  WALNUT_TOKEN_LDA,
  WALNUT_TOKEN_LDR,
  WALNUT_TOKEN_STO,
  WALNUT_TOKEN_ADD,
  WALNUT_TOKEN_SUB,
  WALNUT_TOKEN_MUL,
  WALNUT_TOKEN_DIV,
  WALNUT_TOKEN_MOD,
  WALNUT_TOKE_LBS,
  WALNUT_TOKEN_RBS,
  WALNUT_TOKEN_AND,
  WALNUT_TOKEN_BOR,
  WALNUT_TOKEN_XOR,
  WALNUT_TOKEN_NOT,
  WALNUT_TOKEN_JMP,
  WALNUT_TOKEN_JEQ,
  WALNUT_TOKEN_JNE,
  WALNUT_TOKEN_JGT,
  WALNUT_TOKEN_JLT,
  WALNUT_TOKEN_JGE,
  WALNUT_TOKEN_JLE,
  WALNUT_TOKEN_CMP,
  WALNUT_TOKEN_BRK,
  WALNUT_TOKEN_IWP,
  WALNUT_TOKEN_DWP,
  WALNUT_TOKEN_JSR,
  WALNUT_TOKEN_RET,

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

#endif
