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
void Parser::_handle_start_program()
{
    int tok = this->getNextToken();            
    /* FIXME: getting lines count is still buggy */
    if (tok != this->lexer->tok_start_program) {

    }
    
}


void Parser::_handle_variable_declaration()
{
    this->getNextToken();
    cout << "Variable name" << this->getCurrentLexeme();
}


NumberExprAST * Parser::_handle_number()
{
    double val = strtod(this->getCurrentLexeme().c_str(), NULL);
    return new NumberExprAST(val);
}


/* Public methods follow */
int Parser::getNextToken(void)
{
    /* Check if the program starts with tok_start_program
       Ideally, this should have been the work of the Lexer.
    */
    if (this->start_program) {
        int _first = this->lexer->get_token();
        if (_first != Lexer::tok_start_program)
            throw "Program should start with 'HAI'. Got " + this->getCurrentLexeme();
        this->start_program = false;
    }

    /* All is well, consume the next token */
    return this->lexer->get_token();
}


std::string Parser::getCurrentLexeme(void)
{
    /* Too much abstraction? :D */
    return this->lexer->get_current_identifier();
}


ExprAST* Parser::parse()
{
    try {
        int tok = this->getNextToken();
        switch(tok)
        {
            case Lexer::tok_eof:
                if (this->getCurrentLexeme() != "KTHXBYE")
                    throw "Source program should end with KTHXBYE";
                break;
                
            case Lexer::tok_end_program:
                break; 
                
            case Lexer::tok_number:
                /* Handle numbers */
                return this->_handle_number();
                
            case Lexer::tok_var_decl:
                this->_handle_variable_declaration();
                
            default:
                cout << "Token :" << tok << endl;
        }
    }
    catch(std::string traceback) {
        cout << "Parser Error: " << traceback << endl;
    }
    return NULL;
    
}


int main() {
    Parser *parser = new Parser();
    while(parser->parse())
        ;
}
