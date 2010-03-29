/* 
 *  lexer.h
 *  Author: Sudharshan "Sup3rkiddo" sudharsh@gmail.com>
 *  All Rights Reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#ifndef FATSO_LEXER_H
#define FATSO_LEXER_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>

#include "config.h"

using namespace std;

class Lexer
{
private:
    int last_char;
    int lines;
    std::string identifier; /* The current identifier */
    
    /* Consume the current identifier and get the next identifier.
       Also consume characters in the proceess */
    void get_next_identifier();
    /* Consume one character */
    void consume_char() { this->last_char = getchar(); }
       
public:
    enum tokens {
        /* General keywords */
        tok_eof           = -1, /* <EOF> */
        tok_start_program = -2, /* HAI */
        tok_end_program   = -3, /* KTHXBYE */
        tok_exit          = -4, /* BYES */
        tok_diaf          = -5, /* DIAF */
        tok_end_block     = -6, /* KTHX */
        tok_var_decl      = -7, /* I HAS A - Variable Declaration */
        tok_number        = -8, /* <numbers> [0-9.]+ */
        /* I/O tokens */
        tok_visible       = -9,  /* VISBLE */
        tok_gimmeh        = -10, /* GIMMEH */
        /* Control flow/loop tokens */
        tok_break         = -11, /* GTFO */
        tok_conditional   = -12, /* IZ */
        tok_loop          = -13,
        tok_assignment    = -14, /* R || ITZ */
        tok_binop         = -15,
        tok_invalid       = -100
    };
    /* Given a stream of text. Get tokens */
    int get_token();
    /* Get current lexeme. Note that this DOES NOT consume characters. */
    std::string get_current_identifier();
    /* Return the number of lines (newlines '\n' and carriage feed '\r'
       consumed so far
     */
    int get_lineno();
    /* Check if the lexeme is a binary operator */
    bool is_binary_op(std::string lexeme);
      
    stack<std::string> unknown_identifiers;
};

#endif
