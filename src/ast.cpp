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
/* AST node types follow */

#include "llvm/DerivedTypes.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/LLVMContext.h"
#include "llvm/Support/IRBuilder.h"
#include "ast.h"
#include "parser.h"

using namespace std;
using namespace llvm;

static IRBuilder<> Builder(getGlobalContext());


Value *NumberExprAST::Codegen() {
    return ConstantFP::get(getGlobalContext(), APFloat(val));
}


Value *BinaryExprAST::Codegen() {
    Value *L = LHS->Codegen();
    Value *R = RHS->Codegen();
    if (L == 0 || R == 0) return 0;
    
    if (op == "SUM") return Builder.CreateAdd(L, R, "addtmp");
    if (op == "DIFF") return Builder.CreateSub(L, R, "subtmp");
    if (op == "PRODUCT") return Builder.CreateMul(L, R, "multmp");
    if (op == "QUOSHUNT") return Builder.CreateFDiv(L, R, "divtmp");
        
    throw "Invalid Binary Operator";
  
}


Value *VariableExprAST::Codegen() {
    /* Check the symbol table */
    return this->getValue();
}
