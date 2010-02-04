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
    if (this->current_token != this->lexer->tok_start_program) {
        cout << "Parse error. Program should start with 'HAI'. Got " << this->getCurrentLexeme();
    }
    
}


void Parser::_handle_variable_declaration()
{
    this->getNextToken();
    cout << "Variable name" << this->getCurrentLexeme();
}


void Parser::_handle_end_program()
{
    this->getNextToken();
    if (this->current_token != EOF) 
        throw "Invalid Tokens after KTHXBYE";
   
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
    if (this->current_token == EOF)
        return;
    
    this->_handle_top_level();
    
    while(true) {
        try
        {
            this->getNextToken();
            switch(this->current_token)
                {
                case Lexer::tok_eof:
                    return;
            
                case Lexer::tok_end_program:
                    cout << "Got end Program token" << endl;
                    this->_handle_end_program();
                    break;
                    
                case Lexer::tok_number:
                    /* Handle numbers */
                    break;
                    
                case Lexer::tok_var_decl:
                    this->_handle_variable_declaration();
                    
                default:
                    cout << "Token :" << this->current_token << endl;
                }
            
            
        }
        catch(std::string traceback) {
            cout << "Parser Error: " << traceback << endl;
            continue;
        }
    }
}


int main() {
    Parser *parser = new Parser();
    parser->parse();
    cout << "Current Token " << parser->current_token <<
        "Current Lexeme" << parser->getCurrentLexeme() << endl;
}
