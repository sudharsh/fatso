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


#include "lexer.h"

using namespace std;


/* Private methods follow */
void Lexer::get_next_identifier()
{
    this->identifier = "";
    if (isalnum(this->last_char))
        do { 
            this->identifier += this->last_char;
        } while( isalnum((this->last_char = getchar())) ||
                 this->last_char == '.' ); /* For floating point numbers */
}


/* Public methods follow */
std::string Lexer::get_current_identifier() {
    return this->identifier;
}

int Lexer::get_lines_count() {
    return this->lines;
}


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
    if (this->identifier == "GIMMEH") return Lexer::tok_gimmeh;
    if (this->identifier == "GTFO") return Lexer::tok_break;
    if (this->identifier == "IZ") return Lexer::tok_conditional;
    if (this->identifier == "R" || this->identifier == "ITZ") return Lexer::tok_assignment;
    
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
        return Lexer::tok_loop;
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

    /* Very very wrong
     FIXME: handle negative numbers */
    if (isdigit(this->identifier[0]))
    {
        if (this->identifier.length() == 1)
            return Lexer::tok_number;
        
        bool seen_decimal = false; /* handles cases like 12.3.3 */
        for (int i = 1; i < this->identifier.length(); i++) {
            if((isdigit(this->identifier[i]) || this->identifier[i] == '.'
                || this->identifier[i] == 'E' || this->identifier[i] == 'e' ))
            {
                if (identifier[i] == '.') {
                    if (seen_decimal)
                        break;
                    seen_decimal = true;
                }
                if (i == this->identifier.length() - 1)
                    return Lexer::tok_number;
            }
        }
    }
    if (this->last_char == EOF)
        return Lexer::tok_eof;
    /* Return the last character before consuming it */
    
    this->unknown_identifiers.push(this->identifier);
    return _char;
}
