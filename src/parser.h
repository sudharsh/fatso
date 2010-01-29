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

/* AST node types follow */
#include <iostream>
#include <cstdio>
#include "lexer.h"

using namespace std;


class ExprAST {
public:
    virtual ~ExprAST();
};


class NumberExprAST: public ExprAST {
private:
    double val;
public:
    NumberExprAST(double _val) : val(_val) {}
};


class VariableExprAST: public ExprAST {
private:
    std::string name;
    std::string type;
public:
    VariableExprAST(std::string _name): name(_name) {}
};


class BinaryExprAST: public ExprAST {
private:
    char op;
    ExprAST *LHS, *RHS;
public:
    BinaryExprAST(char _op, ExprAST *_lhs, ExprAST *_rhs):
                  op(_op), LHS(_lhs), RHS(_rhs) {}
};


class Parser
{
private:
    Lexer *lexer;
    /* Handle each type of expression separately */
    void _handle_top_level();

public:
    int current_token;
    
    void getNextToken();
    std::string getCurrentLexeme();
    void parse();
    
    Parser() {
        this->lexer = new Lexer();
    }
};
