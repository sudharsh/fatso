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

#include "llvm/LLVMContext.h"
#include "ast.h"

using namespace std;
using namespace llvm;


Value *NumberExprAST::Codegen() {
    return ConstantFP::get(getGlobalContext(), APFloat(val));
}