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


ExprAST* Parser::_do_variable_assignment(std::string variable_name)
{
    /* Get the value and put it in the symbol table */
    ExprAST *value_ast = this->parse();
    if (!value_ast) 
        throw "Invalid type declaration";
    
    this->symtab[variable_name.c_str()] = value_ast;
    cout << variable_name << ":" << this->symtab[variable_name.c_str()] << endl;
    this->symtab[variable_name.c_str()]->Codegen()->dump();
    return value_ast;
}


bool Parser::_check_symtab(const char * symbol) {
    cout << "-----------" << endl;
    cout << "Symtab address in _check_symtab: " << &this->symtab << endl;
    cout << "Checking for " << symbol << " in the symtab, Count:" << this->symtab.count(symbol) << endl;
    cout << "Symtab size in _check_symtab: " << this->symtab.size() << endl;
    cout << "-----------" << endl;
    if(this->symtab.count(symbol) >= 1) 
        return true;
    return false;
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
        cout << endl << "Parsing " << this->getCurrentLexeme() << endl;
        std::string var;
        
        switch(tok)
        {
            case Lexer::tok_eof:
                break;
                
            case Lexer::tok_end_program:
                break; 
                
            case Lexer::tok_number:
                /* Handle numbers */
                return this->_handle_number();

                
            case Lexer::tok_var_decl:
                this->getNextToken();
                var = this->getCurrentLexeme();
                cout << "Declaring variable " << this->getCurrentLexeme() << endl;                                
                if(this->_check_symtab((var + "|").c_str())) {
                    cout << "Re-assigning" << endl;
                    delete this->symtab[(var + "|").c_str()] ;
                }
                
                this->symtab[(var + "|").c_str()] = NULL;
                cout << "Symtab size after declaring " << var.c_str() << " : " << this->symtab.size() << endl;
                    
                return new VariableExprAST(var);

                
            case Lexer::tok_assignment:
                /*
                  By this time VAR would gotten pushed to unknown_identifiers
                */
                cout << "SymbolTable size: " << this->symtab.size() <<  endl;
                var = this->lexer->unknown_identifiers.top();
                this->lexer->unknown_identifiers.pop();
                return this->_do_variable_assignment(var);
                
                
            default:
                std::string lexeme = this->getCurrentLexeme();
                /* check if current lexeme is in the symtab
                   and do variable assignment if necessary
                */
                cout << "Size of Symtab: before _check_symtab call: " << this->symtab.count(lexeme.c_str()) << endl;
                cout << "Address -->" << &this->symtab << endl;
                cout << "Variables" << endl;
                for(map<const char *, ExprAST *>::const_iterator it = this->symtab.begin();
                    it != this->symtab.end();
                    ++it)
                    cout << it->first << endl;
                
                if(this->_check_symtab((lexeme + "|").c_str()))
                    this->parse();
                break;

        }
        cout << "Last Token :" << tok << endl;
        cout << "Last Lexeme :" << this->getCurrentLexeme() << endl;

    }
    catch(std::string traceback) {
        cout << "Parser Error: " << traceback << endl;
    }
    return NULL;
    
}


int main() {
    Parser *parser = new Parser();
    do
        cout << "ready> " ;
    while(parser->parse());
        
}
