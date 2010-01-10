/* 
 *  lexer.cpp
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

#include <iostream>
#include <cstdio>
#include <cstdlib>

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
    Lexer() : lines(1) { }
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
        tok_loop_start    = -13,
        tok_invalid       = -100
    };
    /* Given a stream of text. Get tokens */
    int get_token();
    /* Return the number of lines (newlines '\n' and carriage feed '\r' */
    int get_lines_count() { return this->lines; }
};


/* Private methods follow */
void Lexer::get_next_identifier()
{
    this->identifier = "";
    if (isalpha(this->last_char))
        do { 
            this->identifier += this->last_char;
        } while( isalnum((this->last_char = getchar())));
}


/* Public methods follow */
int Lexer::get_token()
{
    this->last_char = ' ';
    
    /* Ignore whitespace */
    while(isspace(this->last_char)) {
        if (this->last_char == '\n' || this->last_char == '\r')
            this->lines++;
        this->consume_char();
    }
    /* Track the last known ascii character before consuming the other chars */
    int _char = this->last_char;
    get_next_identifier();

    /* We can probably use a hashmap and do a return map[k]. */
    if (this->identifier == "HAI") return Lexer::tok_start_program;
    if (this->identifier == "KTHXBYE") return Lexer::tok_end_program;
    if (this->identifier == "BYES") return Lexer::tok_exit;
    if (this->identifier == "DIAF") return Lexer::tok_diaf;
    if (this->identifier == "KTHX") return Lexer::tok_end_block;
    if (this->identifier == "VISIBLE") return Lexer::tok_visible;
    if (this->identifier == "GIMMEH") return Lexer::tok_visible;
    if (this->identifier == "GTFO") return Lexer::tok_visible;
    if (this->identifier == "IZ") return Lexer::tok_visible;
    
    /* Variable declarations */
    if (this->identifier == "I") {
        std::string _tokens[] = { "HAS", "A" };
        for (int i = 0; i < 2; i++) {
            this->consume_char();
            get_next_identifier();
            if (this->identifier != _tokens[i])
                return _char;
        }
        return Lexer::tok_var_decl;
    }

    if (this->identifier == "IM") {
        std::string _tokens[] = { "IN", "YR" };
        for (int i = 0; i < 2; i++) {
            this->consume_char();
            get_next_identifier();
            if (this->identifier != _tokens[i])
                return _char;
        }
        return Lexer::tok_var_decl;
    }

    /* Single Line comment */
    if (this->identifier == "BTW") { 
        cout << "Got Comment" << endl;
        while (this->last_char != EOF && this->last_char != '\n' && this->last_char != '\r')
            this->consume_char();
        if (this->last_char != EOF) 
            return this->get_token();
    }
    /* Multiline comment. ignore till TLDR is reached */
    if (this->identifier == "OBTW") {
        cout << "Got multi-line comment" << endl;
        while(this->identifier != "TLDR") {
            this->consume_char();
            get_next_identifier();
        }
        cout << "TLDR reached" << endl;
        if (this->last_char != EOF)
            return this->get_token();
    }

    /* Very very wrong */
    if (isdigit(this->last_char)) {
        bool seen_decimal = false;
        while(isdigit(this->last_char) || this->last_char == '.') {
            if (this->last_char == '.') {
                if (seen_decimal)
                    break;
                seen_decimal = true;
            }
            this->consume_char();
        }
        return Lexer::tok_number;
    }
    if (this->last_char == EOF)
        return Lexer::tok_eof;

    /* Return the last character before consuming it */
    return _char;
}


int main()
{
    Lexer *lexer = new Lexer();
    cout << lexer->get_token();    
}
