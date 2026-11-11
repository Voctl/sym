/*
 * Copyright (c) 2026, Voctl, XSchyt3
 * SPDX-License-Identifier: BSD-2-Clause
 */

// yeah so its our first version - 0.1
// for tokenization, i made a simple tokenization
// enum for our lexer (i will make lexer future)

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TokenKind {
    Eof,        // End of input
    Invalid,    // Invalid token
    Ident,      // Identifier
    Number,     // Numeric literal

    Fn,         // fn
    Let,        // let
    Return,     // return

    Plus,       // +
    Minus,      // -
    Star,       // *
    Slash,      // /
    Caret,      // ^

    Assign,     // =
    Arrow,      // ->

    LParen,     // (
    RParen,     // )
    LBrace,     // {
    RBrace,     // }
    Colon,      // :
    Semicolon,  // ;
    Comma,      // ,
}

#[derive(Debug, Clone, Copy)]
pub struct Token<'src> {
    pub kind: TokenKind,
    pub start: &'src str,
    pub length: usize,
    pub line: usize,
    pub column: usize,
}
