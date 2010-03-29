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
using namespace llvm;


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
    
    this->symtab[variable_name]->value_ast = value_ast;
    cout << variable_name << ":" << this->symtab[variable_name.c_str()] << endl;
    return value_ast;
}


ExprAST* Parser::check_symtab(std::string symbol) {
    if(this->symtab.count(symbol) >= 1) 
        return this->symtab[symbol];
    return NULL;
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

        /* For binops */
        std::string lhs, rhs;
        std::string binary_op;
        
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
                if(this->check_symtab(var)) {
                    cout << "Re-assigning" << endl;
                    delete this->symtab[var] ;
                }
                
                this->symtab[var] = new VariableExprAST(var);
                this->symtab[var]->value_ast = new VoidExprAST(); 
                cout << "Symtab size after declaring " << var.c_str() << " : " << this->symtab.size() << endl;
                return this->symtab[var];

                
            case Lexer::tok_assignment:
                /*
                  By this time VAR would gotten pushed to unknown_identifiers
                */
                cout << "SymbolTable size: " << this->symtab.size() <<  endl;
                var = this->lexer->unknown_identifiers.top();
                this->lexer->unknown_identifiers.pop();
                return this->_do_variable_assignment(var);


            case Lexer::tok_binop:
                binary_op = getCurrentLexeme();
                ExprAST *LHS, *RHS;
                BinaryExprAST *binop;
                
                this->getNextToken(); /* Consume 'OF' */
                if(this->getCurrentLexeme() != "OF") 
                    throw "Invalid BinOp statement. Expected OF";
                
                /* Get LHS */
                LHS = this->parse();
                this->getNextToken(); /* Consume 'AN' */
                if(this->getCurrentLexeme() != "AN") 
                    throw "Invalid BinOp statement. Expected AN";
                
                /* Get RHS */
                RHS = this->parse();
                binop = new BinaryExprAST(binary_op, LHS, RHS);
                return binop;
                
                
            default:
                std::string lexeme = this->getCurrentLexeme();
                /* check if current lexeme is in the symtab
                   and return the node if it is. Otherwise
                */
                if(ExprAST *known_symbol = this->check_symtab(lexeme)) {
                    cout << lexeme << " seems to be a variable" << endl;
                    return known_symbol;
                }
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
