/* 
 *  parser.cpp
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
#include "parser.h"

using namespace std;


/* Private methods follow */
void Parser::_handle_top_level()
{
    /* FIXME: getting lines count is still buggy */
    if (this->current_token != this->lexer->tok_start_program)
        fprintf(stderr, "%d: Parse error. Program should start with 'HAI'", this->lexer->get_lines_count());
}



/* Public methods follow */
void Parser::getNextToken(void) {
    this->current_token = this->lexer->get_token();
}


std::string Parser::getCurrentLexeme(void) {
    /* Too much abstraction? :D */
    return this->lexer->get_current_identifier();
}


void Parser::parse() {
    this->getNextToken();
    switch(this->current_token)
    {
    default:
        this->_handle_top_level();
    }
}


int main() {
    Parser *parser = new Parser();
    parser->parse();
    cout << "Current Token " << parser->current_token <<
        "Current Lexeme" << parser->getCurrentLexeme() << endl;
}
