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
      lexer->pos++;
      lexer->col++;
      if (lexer->source[lexer->pos] == '\n')
        {
          lexer->line++;
          lexer->col = 0;
        }
    }
}

void
number(WalnutLexer *lexer, WalnutToken *tok)
{
  int len = 1;
  while (isdigit(lexer->source[lexer->pos]))
    {
      lexer->pos++;
      lexer->col++;
      len++;
    }

  tok->type   = WALNUT_TOKEN_NUMBER;
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
  // TODO log error
  tok.type   = WALNUT_TOKEN_ERROR;
  tok.length = 1;
  lexer->pos++;
  lexer->col++;

  return tok;
}
