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
#include <stdbool.h>
#include <stdio.h>
#include <walnut/assembler/lexer.h>

void
walnutInitLexer(WalnutLexer *lexer, char *source)
{
  lexer->line   = 1;
  lexer->col    = 1;
  lexer->pos    = 0;
  lexer->source = source;
}

void
skipWhitespace(WalnutLexer *lexer)
{
  while (isspace(lexer->source[lexer->pos]))
    {
      if (lexer->source[lexer->pos] == '\n')
        {
          lexer->line++;
          lexer->col = 0;
        }
      lexer->pos++;
      lexer->col++;
    }
}

void
number(WalnutLexer *lexer, WalnutToken *tok)
{
  int len = 0;
  while (isdigit(lexer->source[lexer->pos]))
    {
      lexer->pos++;
      lexer->col++;
      len++;
    }

  tok->type   = WALNUT_TOKEN_NUMBER;
  tok->length = len;
}

bool
check_op(WalnutLexer *lexer, const char *op)
{
  if (lexer->source[lexer->pos] == op[0])
    {
      lexer->pos++;
      lexer->col++;
      if (lexer->source[lexer->pos] == op[1])
        {
          lexer->pos++;
          lexer->col++;
          return true;
        }
    }
  return false;
}

WalnutTokenType
identifierType(WalnutLexer *lexer)
{
  switch (lexer->source[lexer->pos])
    {
    case 'a':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "dd"))
          {
            return WALNUT_TOKEN_ADD;
          }
        if (check_op(lexer, "nd"))
          {
            return WALNUT_TOKEN_AND;
          }
        break;
      }
    case 'b':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "or"))
          {
            return WALNUT_TOKEN_BOR;
          }
        if (check_op(lexer, "rk"))
          {
            return WALNUT_TOKEN_BRK;
          }
        break;
      }
    case 'c':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "mp"))
          {
            return WALNUT_TOKEN_CMP;
          }
        break;
      }
    case 'd':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "iv"))
          {
            return WALNUT_TOKEN_DIV;
          }
        if (check_op(lexer, "wp"))
          {
            return WALNUT_TOKEN_DWP;
          }
        break;
      }
    case 'h':
      {
        lexer->pos++;
        lexer->col++;
        return check_op(lexer, "lt") ? WALNUT_TOKEN_HLT
                                     : WALNUT_TOKEN_IDENTIFIER;
        break;
      }
    case 'i':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "wp"))
          {
            return WALNUT_TOKEN_IWP;
          }
        break;
      }
    case 'j':
      {
        if (check_op(lexer, "mp"))
          {
            return WALNUT_TOKEN_JMP;
          }
        if (check_op(lexer, "eq"))
          {
            return WALNUT_TOKEN_JEQ;
          }
        if (check_op(lexer, "ne"))
          {
            return WALNUT_TOKEN_JNE;
          }
        if (check_op(lexer, "gt"))
          {
            return WALNUT_TOKEN_JGT;
          }
        if (check_op(lexer, "lt"))
          {
            return WALNUT_TOKEN_JLT;
          }
        if (check_op(lexer, "ge"))
          {
            return WALNUT_TOKEN_JGE;
          }
        if (check_op(lexer, "le"))
          {
            return WALNUT_TOKEN_JLE;
          }
        if (check_op(lexer, "sr"))
          {
            return WALNUT_TOKEN_JSR;
          }
        break;
      }
    case 'l':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "di"))
          {
            return WALNUT_TOKEN_LDI;
          }
        if (check_op(lexer, "da"))
          {
            return WALNUT_TOKEN_LDA;
          }
        if (check_op(lexer, "dr"))
          {
            return WALNUT_TOKEN_LDR;
          }
        if (check_op(lexer, "bs"))
          {
            return WALNUT_TOKE_LBS;
          }
        break;
      }
    case 'm':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "ul"))
          {
            return WALNUT_TOKEN_MUL;
          }
        if (check_op(lexer, "od"))
          {
            return WALNUT_TOKEN_MOD;
          }
        break;
      }
    case 'n':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "ot"))
          {
            return WALNUT_TOKEN_NOT;
          }
        break;
      }
    case 'r':
      {
        lexer->pos++;
        lexer->col++;
        int oldpos = lexer->pos;
        int oldcol = lexer->col;
        if (check_op(lexer, "bs"))
          {
            return WALNUT_TOKEN_RBS;
          }
        if (check_op(lexer, "et"))
          {
            return WALNUT_TOKEN_RET;
          }

        lexer->pos = oldpos;
        lexer->col = oldcol;
        while (isdigit(lexer->source[lexer->pos]))
          {
            lexer->pos++;
            lexer->col++;
          }
        int eon = lexer->pos;
        while (isalpha(lexer->source[lexer->pos])
               || isdigit(lexer->source[lexer->pos])
               || lexer->source[lexer->pos] == '_')
          {
            lexer->pos++;
            lexer->col++;
          }
        if (eon == lexer->pos)
          {
            return WALNUT_TOKEN_REG;
          }

        break;
      }
    case 's':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "to"))
          {
            return WALNUT_TOKEN_STO;
          }
        if (check_op(lexer, "ub"))
          {
            return WALNUT_TOKEN_SUB;
          }
        break;
      }
    case 'x':
      {
        lexer->pos++;
        lexer->col++;
        if (check_op(lexer, "xor"))
          {
            return WALNUT_TOKEN_XOR;
          }
        break;
      }
    }
  while (isalpha(lexer->source[lexer->pos])
         || isdigit(lexer->source[lexer->pos])
         || lexer->source[lexer->pos] == '_')
    {
      lexer->pos++;
      lexer->col++;
    }
  return WALNUT_TOKEN_IDENTIFIER;
}

void
identifier(WalnutLexer *lexer, WalnutToken *tok)
{
  int len = 0;
  while (isalpha(lexer->source[lexer->pos])
         || isdigit(lexer->source[lexer->pos])
         || lexer->source[lexer->pos] == '_')
    {
      lexer->pos++;
      len++;
    }
  lexer->pos -= len;
  tok->type   = identifierType(lexer);
  tok->length = len;
}

WalnutToken
walnutLexToken(WalnutLexer *lexer)
{
  skipWhitespace(lexer);
  WalnutToken tok;
  tok.line  = lexer->line;
  tok.col   = lexer->col;
  tok.start = lexer->source + lexer->pos;

  char c = lexer->source[lexer->pos];
  if (c == ',')
    {
      tok.type   = WALNUT_TOKEN_COMMA;
      tok.length = 1;
      lexer->pos++;
      lexer->col++;
      return tok;
    }
  if (c == '\0')
    {
      tok.type   = WALNUT_TOKEN_EOF;
      tok.length = 1;
      lexer->pos++;
      lexer->col++;
      return tok;
    }
  if (isdigit(c))
    {
      number(lexer, &tok);
      return tok;
    }
  if (isalpha(c) || c == '_')
    {
      identifier(lexer, &tok);
      return tok;
    }
  // TODO log error
  tok.type   = WALNUT_TOKEN_ERROR;
  tok.length = 1;
  lexer->pos++;
  lexer->col++;

  return tok;
}
