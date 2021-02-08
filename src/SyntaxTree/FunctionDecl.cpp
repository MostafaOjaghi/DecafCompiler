//
// Created by shengdebao on 2/5/21.
//

#include "FunctionDecl.h"

const std::string &SyntaxTree::FunctionDecl::getFunctionIdentifier() const {
    return functionIdentifier;
}

void SyntaxTree::FunctionDecl::setFunctionIdentifier(const std::string &functionIdentifier) {
    FunctionDecl::functionIdentifier = functionIdentifier;
}

SyntaxTree::Formals *SyntaxTree::FunctionDecl::getFormals() const {
    return formals;
}

void SyntaxTree::FunctionDecl::setFormals(SyntaxTree::Formals *formals) {
    FunctionDecl::formals = formals;
}

SyntaxTree::StmtBlock *SyntaxTree::FunctionDecl::getStmtBlock() const {
    return stmtBlock;
}

void SyntaxTree::FunctionDecl::setStmtBlock(SyntaxTree::StmtBlock *stmtBlock) {
    FunctionDecl::stmtBlock = stmtBlock;
}

void SyntaxTree::FunctionDecl::handleScope() {
    this->getFormals()->setScope(this->getScope());
    this->getFormals()->handleScope();
    SymbolTable::Scope *scopeStmtBlock = new SymbolTable::Scope();
    scopeStmtBlock->setPar(this->getScope());
    this->getStmtBlock()->setScope(scopeStmtBlock);
    this->getStmtBlock()->handleScope();
}

SyntaxTree::Cgen SyntaxTree::FunctionDeclToVoidIdent::cgen() {
    Cgen cgen;
    cgen.code += "Label func_" + getFunctionIdentifier() + ":\n"; // TODO args
    cgen.code += "Beginfunc 100\n";
    cgen.code += getStmtBlock()->cgen().code;
    cgen.code += "Endfunc\n";

    return cgen;
}
