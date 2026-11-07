/*
 * Copyright (c) 2026, Voctl
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#include <stddef.h>


/* yeah so its our first version - 0.1
   for tokenization, i made a simple tokenization
   enum for our lexer (i will make lexer future)
 */

typedef enum {
    TOKEN_EOF,        /* End of input */
    TOKEN_INVALID,    /* Invalid token */
    TOKEN_IDENT,      /* Identifier */
    TOKEN_NUMBER,     /* Numeric literal */

    TOKEN_FN,         /* fn */
    TOKEN_LET,        /* let */
    TOKEN_RETURN,     /* return */

    TOKEN_PLUS,       /* + */
    TOKEN_MINUS,      /* - */
    TOKEN_STAR,       /* * */
    TOKEN_SLASH,      /* / */
    TOKEN_CARET,      /* ^ */

    TOKEN_ASSIGN,     /* = */
    TOKEN_ARROW,      /* -> */

    TOKEN_LPAREN,     /* ( */
    TOKEN_RPAREN,     /* ) */
    TOKEN_LBRACE,     /* { */
    TOKEN_RBRACE,     /* } */
    TOKEN_COLON,      /* : */
    TOKEN_SEMICOLON,  /* ; */
    TOKEN_COMMA       /* , */
} TokenKind;

typedef struct {
    TokenKind kind;       /* Token type, e.g. TOKEN_NUMBER or TOKEN_PLUS */
    const char *start;    /* Pointer to the first character in the source */
    size_t length;        /* Number of characters in the token */
    size_t line;          /* 1-based source line */
    size_t column;        /* 1-based source column */
} Token;



#endif // TOKEN_H_
