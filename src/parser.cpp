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


ExprAST* Parser::_do_variable_assignment(std::string variable_name, IRBuilder<> Builder)
{
    /* Get the value and put it in the symbol table */
    ExprAST *value_ast = this->parse(Builder);
    if (!value_ast) 
        throw new ParserError("valid type declaration", this->lexer->get_lineno());
    this->symtab[variable_name]->value_ast = value_ast;
    cout << this->symtab[variable_name]->getNodeRepr() << endl; 
    return this->symtab[variable_name];
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
            throw new ParserError("Program should start with 'HAI'. Got " + this->getCurrentLexeme(), this->lexer->get_lineno());
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


ExprAST* Parser::parse(IRBuilder<> Builder)
{

    int tok = this->getNextToken();
    
    cout << endl << "Parsing " << this->getCurrentLexeme() << endl;
    std::string var;

    /* For binops */
    std::string lhs, rhs;
    std::string binary_op;

    switch(tok)
        {
        case Lexer::tok_eof:
            return NULL;
                
        case Lexer::tok_end_program:
            return NULL;
                
        case Lexer::tok_number:
            /* Handle numbers */
            return this->_handle_number();

                
        case Lexer::tok_var_decl:

            ExprAST *void_ast;
            void_ast = new VoidExprAST();
            
            this->getNextToken();
            var = this->getCurrentLexeme();
            cout << "Declaring variable " << this->getCurrentLexeme() << endl;                                
            if(this->check_symtab(var)) {
                cout << "Re-assigning" << endl;
                delete this->symtab[var];
                this->symtab[var] = new VariableExprAST(var);
            }
            
            this->symtab[var] = new VariableExprAST(var);
            this->symtab[var]->value_ast = void_ast;
            cout << "Symtab size after declaring " << var.c_str() << " : " << this->symtab.size() << endl;
            return this->symtab[var];

        case Lexer::tok_assignment:
            /*
              By this time VAR would gotten pushed to unknown_identifiers
            */
            var = this->lexer->unknown_identifiers.top();
            this->lexer->unknown_identifiers.pop();
            return this->_do_variable_assignment(var, Builder);


        case Lexer::tok_binop:
            binary_op = getCurrentLexeme();
            ExprAST *LHS, *RHS;
            BinaryExprAST *binop;
                
            this->getNextToken(); /* Consume 'OF' */
            if(this->getCurrentLexeme() != "OF") 
                throw new ParserError("Invalid BinOp statement. Expected OF", this->lexer->get_lineno());
                
            /* Get LHS */
            LHS = this->parse(Builder); 
            this->getNextToken(); /* Consume 'AN' */
            if(this->getCurrentLexeme() != "AN") 
                throw new ParserError("Invalid BinOp statement. Expected AN", this->lexer->get_lineno());
                
            /* Get RHS */
            RHS = this->parse(Builder);
            binop = new BinaryExprAST(binary_op, LHS, RHS);
            if (!binop)
                throw new ParserError("Invalid Operation.", this->lexer->get_lineno());
            return binop;
                
                
        default:
            std::string lexeme = this->getCurrentLexeme();
            /* check if current lexeme is in the symtab
               and return the node if it is. Otherwise
            */
            if(ExprAST *known_symbol = this->check_symtab(lexeme)) {
                cout << lexeme << " seems to be a variable" << endl;
                return this->symtab[lexeme];
            }
            break;

        }
    
    throw new ParserError("Unknown token: " + this->getCurrentLexeme() + ":::", this->lexer->get_lineno());
    
}
