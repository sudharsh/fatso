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
#include <sstream>
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
    virtual std::string getNodeType() = 0;
};


class NumberExprAST: public ExprAST {
private:
    double val;
public:
    //double get_val() { return this->val; }
    virtual std::string getNodeType() {
        std::ostringstream o;
        o << this->val;
        return o.str();
    }
    NumberExprAST(double _val) : val(_val) {}
    virtual Value *Codegen();
};


class VariableExprAST: public ExprAST {
private:
    std::string name;
    std::string type; /* FIXME: Not implemented yet */

public:
    ExprAST *value_ast;
    Value *getValue() { return this->value_ast->Codegen(); }
    virtual std::string getNodeType() {
        return "VARIABLE holding " + this->value_ast->getNodeType();
    }
    VariableExprAST(std::string _name): name(_name) {}
    virtual Value *Codegen();
};


class BinaryExprAST: public ExprAST {
private:
    std::string op;
    ExprAST *LHS, *RHS;
public:
    BinaryExprAST(std::string _op, ExprAST *_lhs, ExprAST *_rhs):
    op(_op), LHS(_lhs), RHS(_rhs) {};
    virtual Value *Codegen();
    virtual std::string getNodeType() { return "BINARY Expression holding " + this->LHS->getNodeType() + " and " \
            + this->RHS->getNodeType(); }
};


class VoidExprAST: public ExprAST {
public:
    virtual Value *Codegen();
    virtual std::string getNodeType() { return "VOID Node"; }
};
    


/* Main Function AST, hold the others.
   since there is no concept of functions.
   Think of this as a root node of the syntax tree
*/
class MainFunction {
private:
    ExprAST *body;
public:
    Function *Codegen();
};    


#endif

