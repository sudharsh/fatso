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

using namespace std;


class Lexer
{
private:
    int last_char;
    std::string identifier; /* The current identifier */
    
    /* Consume the current identifier and get the next identifier.
       Also consume characters in the proceess */
    void get_next_identifier();

    /* Consume one character */
    void consume_char() { this->last_char = getchar(); }
public:
    enum tokens {
        tok_eof           = -1, /* <EOF> */
        tok_start_program = -2, /* HAI */
        tok_end_program   = -3, /* KTHXBYE */
        tok_var_decl      = -4, /* I HAS A - Variable Declaration */
        tok_number        = -5,
        tok_invalid       = 0
    };
    /* Given a stream of text. Get tokens */
    int get_token();
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
    while(isspace(this->last_char)) 
        this->consume_char();

    /* Track the last known ascii character before consuming the other chars */
    int _char = this->last_char;
    get_next_identifier();

    if (this->identifier == "HAI") return Lexer::tok_start_program;
    if (this->identifier == "KTHXBYE") return Lexer::tok_end_program;

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

    if (isdigit(this->last_char) || this->last_char == '.') {
        std::string num_str;
        do {
            num_str += this->last_char;
            this->last_char = getchar();
        } while (isdigit(this->last_char) || this->last_char == '.');
        num_str = strtod(num_str.c_str(), 0);
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
