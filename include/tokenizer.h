/*
 * Copyright (c) 2026, Voctl
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_
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

    // conditional things
    TOKEN_IF,       /* if */
    TOKEN_ELSE,     /* else */
    TOKEN_WHILE,    /* while */
    TOKEN_TRUE,     /* true */
    TOKEN_FALSE     /* false */
} TokenKind;

// Struct of a Token
typedef struct {
    TokenKind kind;       //  Token type
    const char *start;    //  Pointer to the first character in the source
    size_t length;        //  Number of characters in the token
    size_t line;          //  1-based source line
    size_t column;        //  1-based source column
} Token;

// Struct of a Lexer (its very simple for now)
typedef struct Lexer {
  const char* source;
  size_t cursor;
} Lexer;


#endif // TOKENIZER_H_
