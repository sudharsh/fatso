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
NumberExprAST * Parser::_handle_number()
{
    double val = strtod(this->getCurrentLexeme().c_str(), NULL);
    NumberExprAST *number_ast = new NumberExprAST(val);
    return number_ast;
}


VariableExprAST * Parser::_handle_variable_declaration()
{
    /* Get the variable */
    this->getNextToken();
    std::string variable = this->getCurrentLexeme();
    VariableExprAST *node = new VariableExprAST(variable);

    /* Check if the variable is defined in one go
       eg, I HAS A VAR *ITZ 12*
    */
    cout << "Declaring " << variable.c_str() << endl;
    this->symtab[variable.c_str()] = node;

    cout << this->symtab[variable.c_str()] << endl;
    return (VariableExprAST *)&this->symtab[variable.c_str()];
}


ExprAST* Parser::_do_variable_assignment(std::string variable_name)
{
    /* Get the value and put it in the symbol table */
    ExprAST *value_ast = this->parse();
    if (!value_ast) 
        throw "Invalid type declaration";
    this->symtab[variable_name.c_str()] = value_ast;
    cout << variable_name << ":" << this->symtab[variable_name.c_str()];
    this->symtab[variable_name.c_str()]->Codegen()->dump();
    return value_ast;
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
        string var;
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
                return this->_handle_variable_declaration();

            case Lexer::tok_assignment:
                /*
                  By this time VAR would gotten pushed to unknown_identifiers
                */
                var = this->lexer->unknown_identifiers.top();
                this->lexer->unknown_identifiers.pop();
                cout << "Checking " << var << endl;
                return this->_do_variable_assignment(var);
                
            default:
                std::string lexeme = this->getCurrentLexeme();
                map<const char *, ExprAST *>::iterator it = this->symtab.begin();
                it = this->symtab.find(lexeme.c_str());
                cout << this->symtab[lexeme.c_str()];
                if(it != this->symtab.end()) {
                    this->parse();
                }

                cout << "Token :" << tok << endl;
                cout << "Lexeme : d" << lexeme << endl;
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
