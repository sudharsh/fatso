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
    
    /* Get the current identifier. Also consume characters in the proceess */
    void update_current_identifier();
public:
    enum tokens {
        tok_comment = -1,
        tok_invalid = 0
    };
    /* Given a stream of text. Get tokens */
    int get_token();
};


/* Private methods follow */
void Lexer::update_current_identifier()
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
    this->identifier = "";
    
    /* Ignore whitespace */
    while(isspace(this->last_char))
        this->last_char = getchar();

    update_current_identifier();        
    cout << "this->identifier" << this->identifier << endl;

    /* Single Line comment */
    if (this->identifier == "BTW") { 
        cout << "Got Comment" << endl;
        do
            this->last_char = getchar();
        while (this->last_char != EOF && this->last_char != '\n' && this->last_char != '\r');
                
        if (this->last_char != EOF) 
            return this->get_token();
    }
    /* Multiline comment. ignore till TLDR is reached */
    else if (this->identifier == "OBTW") {
        cout << "Got multi-line comment" << endl;
        while(this->identifier != "TLDR") {
            this->last_char = getchar();
            update_current_identifier();
        }
        cout << "TLDR reached" << endl;
        if (this->last_char != EOF)
            return this->get_token();
    }
    
    return Lexer::tok_invalid;
}


int main()
{
    Lexer *lexer = new Lexer();
    cout << lexer->get_token();    
}
