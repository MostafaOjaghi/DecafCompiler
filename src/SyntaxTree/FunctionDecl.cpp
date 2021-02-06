//
// Created by shengdebao on 2/5/21.
//

#include "FunctionDecl.h"

const std::string &SyntaxTree::FunctionDeclToVoidIdent::getFunctionIdentifier() const {
    return functionIdentifier;
}

void SyntaxTree::FunctionDeclToVoidIdent::setFunctionIdentifier(const std::string &functionIdentifier) {
    FunctionDeclToVoidIdent::functionIdentifier = functionIdentifier;
}

SyntaxTree::Formals *SyntaxTree::FunctionDeclToVoidIdent::getFormals() const {
    return formals;
}

void SyntaxTree::FunctionDeclToVoidIdent::setFormals(SyntaxTree::Formals *formals) {
    FunctionDeclToVoidIdent::formals = formals;
}

SyntaxTree::StmtBlock *SyntaxTree::FunctionDeclToVoidIdent::getStmtBlock() const {
    return stmtBlock;
}

void SyntaxTree::FunctionDeclToVoidIdent::setStmtBlock(SyntaxTree::StmtBlock *stmtBlock) {
    FunctionDeclToVoidIdent::stmtBlock = stmtBlock;
}

SyntaxTree::Cgen SyntaxTree::FunctionDeclToVoidIdent::cgen() {
    Cgen cgen;
    cgen.code += "Label " + functionIdentifier + ":\n";
    cgen.code += "BeginFunc 100\n"; // TODO correct
    cgen.code += stmtBlock->cgen().code;
    return cgen;
}
