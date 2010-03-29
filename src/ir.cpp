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
    IRBuilder<> Builder(Context);
    
    Parser *parser = new Parser();
    parser->module = new Module("FATSO JIT", Context);

    /* The main() for LOLCODE
     */

    /* Create the top level interpreter function to call as entry */
    
    FunctionType *ftype = FunctionType::get(Type::getVoidTy(Context), false);
    Function *mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", parser->module);
    BasicBlock *bblock = BasicBlock::Create(Context, "__main", mainFunction, 0);

    Builder.SetInsertPoint(bblock);
    //Builder.Insert(CallIn
        
    //iplist<Instruction>
    try{
        while(ExprAST *ast = parser->parse())
        {
            cout << bblock->getInstList().empty() <<endl;
            //ast->Codegen()->dump();
            //Instruction *i = (Instruction *)ast->Codegen();
            //        Builder.Insert(i);
        }
    }
    catch (ParserError *error) {
        cout << "For fuck's sake" << endl;
        cout << error->get_reason();
    }

    Builder.CreateRetVoid();
    verifyFunction(*mainFunction);
    parser->module->dump();
    return 0;
}
