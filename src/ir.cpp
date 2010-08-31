/* 
 *  ir.cpp
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

#include "parser.h"


using namespace std;
using namespace llvm;


int main() {
    LLVMContext &Context = getGlobalContext();
    cout << &Context << endl;
    cout << &getGlobalContext() << endl;
    IRBuilder<> Builder(Context);
    
    Parser *parser = new Parser("MAIN", Context);

    /* The main() for LOLCODE
     */

    /* Create the top level interpreter function to call as entry */
    FunctionType *ftype = FunctionType::get(Type::getDoubleTy(Context), false);
    Function *mainFunction = Function::Create(ftype, GlobalValue::ExternalLinkage, "main", parser->module);
    BasicBlock *bblock = BasicBlock::Create(Context, "__main", mainFunction, 0);

    Builder.SetInsertPoint(bblock);
        
    //iplist<Instruction>
    try{
        while(ExprAST *ast = parser->parse(Builder))
        {
            Instruction *i = cast<Instruction>(ast->Codegen(Builder));
            bblock->getInstList().push_back(i);
            //ast->Codegen(Builder)->dump();
        }
    }
    catch (ParserError *error) {
        cout << "PARSE ERROR: " << error->get_reason() << endl;
    }

    ExprAST *ret = new NumberExprAST(0);
    Builder.CreateRetVoid();
    //verifyFunction(*mainFunction);
    parser->module->dump();
    return 0;
}
