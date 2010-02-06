/* 
 *  ast.cpp
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

/* Definition for Abstract Syntax Trees go in here */
#ifndef FATSO_AST_H
#define FATSO_AST_H

#include <iostream>
#include <cstdio>
#include <map>
#include "llvm/DerivedTypes.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Support/IRBuilder.h"

#include "lexer.h"

using namespace std;
using namespace llvm;


class ExprAST {
public:
    virtual ~ExprAST() {}
    virtual Value *Codegen() = 0;
};


class NumberExprAST: public ExprAST {
private:
    double val;
public:
    NumberExprAST(double _val) : val(_val) {}
    virtual Value *Codegen();
};


class VariableExprAST: public ExprAST {
private:
    std::string name;
    std::string type; /* FIXME: Not implemented yet */

    ExprAST *value;
public:
    VariableExprAST(std::string _name): name(_name) {}
    VariableExprAST(std::string _name, ExprAST *_value): value(_value), name(_name) {}
    virtual Value *Codegen() {};
};


class BinaryExprAST: public ExprAST {
private:
    char op;
    ExprAST *LHS, *RHS;
public:
    BinaryExprAST(char _op, ExprAST *_lhs, ExprAST *_rhs):
    op(_op), LHS(_lhs), RHS(_rhs) {};
    virtual Value *Codegen() {};
};


#endif

