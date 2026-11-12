/*
 * Copyright (c) 2026, Voctl
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "tokenizer.h"

/* So, its a simplified
   And we also trying to write a scanner
   and it will be main algorithm for our scanner
   If u look at the func, u will see its look like
   pseudocode, because, it is.
*/
/* Token lex_token(Lexer *lexer) { */
/*     skip_trivia(lexer); */

/*     usize start = lexer->cursor; */

/*     if (at_end(lexer)) { */
/*         return make_token(lexer, start, TOKEN_EOF); */
/*     } */

/*     char c = advance(lexer); */

/*     if (is_identifier_start(c)) { */
/*         return lex_identifier(lexer, start); */
/*     } */

/*     if (is_digit(c)) { */
/*         return lex_number(lexer, start); */
/*     } */

/*     switch (c) { */
/*     case '+': return make_token(lexer, start, TOKEN_PLUS); */
/*     case '(': return make_token(lexer, start, TOKEN_LEFT_PAREN); */
/*     case ')': return make_token(lexer, start, TOKEN_RIGHT_PAREN); */
/*     default: return make_token(lexer, start, TOKEN_INVALID); */
/*     } */
/* } */



// this function check for a delimiter(it is a piece of data
// that seprated it from other) to peform some specif case
// on it
bool isDelimiter(char chr)
{
  return (chr == ' ' || chr == '+' || chr == '-'
          || chr == '*' || chr == '/' || chr == ','
          || chr == ';' || chr == '%' || chr == '>'
          || chr == '<' || chr == '=' || chr == '('
          || chr == ')' || chr == '[' || chr == ']'
          || chr == '{' || chr == '}');
}

// this function check for a valid identifier eg:- +,-* etc
bool isOperator(char chr)
{
  return (chr == '+' || chr == '-' || chr == '*'
          || chr == '/' || chr == '>' || chr == '<'
          || chr == '=');
}

// this function check for an valid identifier
bool isValidIdentifier(char* str)
{
  return (str[0] != '0' && str[0] != '1' && str[0] != '2'
          && str[0] != '3' && str[0] != '4'
          && str[0] != '5' && str[0] != '6'
          && str[0] != '7' && str[0] != '8'
          && str[0] != '9' && !isDelimiter(str[0]));
}

// 32 Keywords are checked in this function and return the
// result accordingly
bool isKeyword(char* str)
{

  // our keywords
  const char* keywords[]
    = { "fn", "let", "return", "if",
        "else", "while", "true", "false"};


  for (int i = 0;
       i < sizeof(keywords) / sizeof(keywords[0]); i++) {
    if (strcmp(str, keywords[i]) == 0) {
      return true;
    }
  }
  return false;
}

// check for an integer value
bool isInteger(char* str)
{
  if (str == NULL || *str == '\0') {
    return false;
  }
  int i = 0;
  while (isdigit(str[i])) {
    i++;
  }
  return str[i] == '\0';
}
