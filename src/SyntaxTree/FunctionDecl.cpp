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
    auto *formalsScope = new SymbolTable::Scope("func_" + functionIdentifier, getScope());
    auto *scopeStmtBlock = new SymbolTable::Scope("body", formalsScope);

    formals->setScope(formalsScope);
    formals->handleScope();
    stmtBlock->setScope(scopeStmtBlock);
    stmtBlock->handleScope();
}

SyntaxTree::Cgen SyntaxTree::FunctionDecl::cgen() {
    Cgen cgen;
    Cgen body = getStmtBlock()->cgen();
    std::string args;
    for (Variable *arg : formals->getVariables()) {
        args += " " + formals->getScope()->getEntry(arg->getId())->getUniqueId();
    }
    cgen.append("Label func_" + getFunctionIdentifier() + ":" + args + "\n");
    cgen.append("Beginfunc " + std::to_string(body.var_count * 4) + "\n");
    cgen.append(body);
    cgen.append("Endfunc\n");

    return cgen;
}

SyntaxTree::Cgen SyntaxTree::FunctionDeclToVoidIdent::cgen() {
    return FunctionDecl::cgen();
}
