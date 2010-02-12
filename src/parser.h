/* 
 *  parser.h
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

#ifndef FATSO_PARSER_H
#define FATSO_PARSER_H

#include "ast.h"

using namespace std;
using namespace llvm;

class Parser
{
private:
    Lexer *lexer;
    bool start_program;
    map<std::string, ExprAST *> symtab; /* FIXME: Deprecated
                                            Rudimentary symbol table */
    Module *module;
    IRBuilder<> Builder();
       
    /* Handle each type of expression separately */
    VariableExprAST *_handle_variable_declaration();
    NumberExprAST *_handle_number();

    ExprAST* _do_variable_assignment(std::string);

    bool _check_symtab(std::string);
    
public:
    int getNextToken();
    std::string getCurrentLexeme();
    ExprAST* parse();
           
    Parser ()  {
        this->start_program = true;
        this->lexer = new Lexer();
    }
};

#endif
