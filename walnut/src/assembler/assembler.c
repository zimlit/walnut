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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <walnut/assembler/assembler.h>
#include <walnut/opcode.h>

typedef enum
{
  TOKEN_HLT,
  TOKEN_LDI,

  TOKEN_REG,
  TOKEN_NUMBER,
  TOKEN_COMMA,

  TOKEN_ERROR,
  TOKEN_EOF,
} TokenType;

typedef struct
{
  TokenType type;
  int line;
  int col;
  char *start;
  char *end;
} Token;

typedef struct
{
  int line;
  int col;
  int pos;
  const char *source;
} Lexer;

void
initLexer(Lexer *lexer, const char *source)
{
  lexer->line   = 1;
  lexer->col    = 1;
  lexer->pos    = 0;
  lexer->source = source;
}

Token
lexToken(Lexer *lexer)
{
  Token tok;
  tok.line = lexer->line;
  tok.col  = lexer->col;
  while (isspace(lexer->source[lexer->pos]))
    {
      lexer->pos++;
      lexer->col++;
      if (lexer->source[lexer->pos] == '\n')
        {
          lexer->line++;
          lexer->col = 0;
        }
    }

  char c = lexer->source[lexer->pos];
  if (c == ',')
    {
      tok.type  = TOKEN_COMMA;
      tok.start = lexer->source + lexer->pos;
      tok.end   = tok.start;
      lexer->pos++;
      lexer->col++;
      return tok;
    }
  else if (c == '\0')
    {
      tok.type  = TOKEN_EOF;
      tok.start = lexer->source + lexer->pos;
      tok.end   = tok.start;
      lexer->pos++;
      lexer->col++;
    }
  else
    {
      // TODO log error
      tok.type  = TOKEN_ERROR;
      tok.start = lexer->source + lexer->pos;
      tok.end   = tok.start;
      lexer->pos++;
      lexer->col++;
    }

  return tok;
}

void
walnutAssemblerOutputInit(WalnutAssemblerOutput *output)
{
  output->data     = NULL;
  output->cap      = 0;
  output->len      = 0;
  output->hadError = false;
}

void
walnutAssemblerOutputPush(WalnutAssemblerOutput *output, uint64_t item)
{
  if (output->len + 1 > output->cap)
    {
      output->cap  = output->cap ? output->cap * 2 : 64;
      output->data = realloc(output->data, output->cap);
    }
  output->data[output->len] = item;
  output->len++;
}

void
walnutAssemblerOutputFree(WalnutAssemblerOutput *output)
{
  free(output->data);
  walnutAssemblerOutputInit(output);
}

WalnutAssemblerOutput
walnutAssemble(const char *source)
{
  WalnutAssemblerOutput output;
  walnutAssemblerOutputInit(&output);

  return output;
}