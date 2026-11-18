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
#include <math.h>
#include <limits.h>
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

enum {
    TOK_NULL = TE_CLOSURE7+1, TOK_ERROR, TOK_END, TOK_SEP,
    TOK_OPEN, TOK_CLOSE, TOK_NUMBER, TOK_VARIABLE, TOK_INFIX
};

enum {
    PREC_NONE, PREC_LIST, PREC_OR, PREC_AND, PREC_EQ,
    PREC_REL, PREC_SUM, PREC_TERM, PREC_POW
};

// state structure
typedef struct state {
    const char *next;
    int type;
    int prec;
    union {double value; const double *bound; const void *function;};
    void *context;

    const te_variable *lookup;
    int lookup_len;
    int applied_unary;
    int depth;
} state;


static const double exact_pow10[] = {
    1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11,
    1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19, 1e20, 1e21, 1e22
};

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


  for (size_t i = 0;
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



// i stole this from from tinyexpr repo
static double parse_number(state *s) {
    /* Parses a decimal or hex constant manually, so that the result does
       not depend on LC_NUMERIC. Sets s->type. */
    const char *p = s->next;
    double value = 0.0;

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X') &&
        isxdigit((unsigned char)p[2])) {
        p += 2;
        while (isxdigit((unsigned char)p[0])) {
            const char c = p[0];
            const int d = isdigit((unsigned char)c) ? c - '0' :
                          (c >= 'a' ? c - 'a' + 10 : c - 'A' + 10);
            value = value * 16.0 + d;
            p++;
        }
    } else {
        int exponent = 0, digits = 0;

        while (isdigit((unsigned char)p[0])) {
            value = value * 10.0 + (p[0] - '0');
            p++; digits++;
        }

        if (p[0] == '.') {
            p++;
            while (isdigit((unsigned char)p[0])) {
                value = value * 10.0 + (p[0] - '0');
                p++; digits++; exponent--;
            }
        }

        if (digits == 0) {
            /* A lone '.' is not a number. */
            s->type = TOK_ERROR;
            return 0.0;
        }

        if (p[0] == 'e' || p[0] == 'E') {
            /* Only consume the exponent if digits follow it, so that
               "1e" still parses as the number 1 then the variable e. */
            const char *ep = p + 1;
            int esign = 1, e = 0;

            if (ep[0] == '+') {
                ep++;
            } else if (ep[0] == '-') {
                esign = -1;
                ep++;
            }

            if (isdigit((unsigned char)ep[0])) {
                while (isdigit((unsigned char)ep[0])) {
                    if (e < 100000000) e = e * 10 + (ep[0] - '0');
                    ep++;
                }
                exponent += esign * e;
                p = ep;
            }
        }

        /* The zero check keeps a huge exponent from producing 0 * inf. */
        if (exponent && value != 0.0) {
            if (exponent < 0 && exponent >= -22) {
                value /= exact_pow10[-exponent];
            } else {
                value *= pow(10.0, exponent);
            }
        }
    }
}
