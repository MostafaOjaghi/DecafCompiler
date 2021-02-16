//
// Created by shengdebao on 2/5/21.
//

#include "FunctionDecl.h"
#include "SymbolTable/SymbolTableEntry.h"

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

    SymbolTable::TypeName typeName =this->getType()->getTypeName();
    bool isFunction = true;
    auto *entry = new SymbolTable::SymbolTableEntry(functionIdentifier, typeName, this->getScope(), isFunction);
    for (Variable *formal : formals->getVariables())
        entry->addFormal(formal->getType()->getTypeName());
    this->getScope()->addEntry(functionIdentifier, entry);

    formals->setScope(formalsScope);
    formals->handleScope();
    stmtBlock->setScope(scopeStmtBlock);
    stmtBlock->handleScope();
}

SyntaxTree::Cgen SyntaxTree::FunctionDecl::cgen() {
    Cgen cgen;
    Cgen body = getStmtBlock()->cgen();
    cgen.append("Beginfunc " + std::to_string(body.var_count * 4) + "\n");
    cgen.append(body);
    cgen.append("Endfunc\n");

    return cgen;
}

SyntaxTree::Type *SyntaxTree::FunctionDecl::getType() const {
    return type;
}

void SyntaxTree::FunctionDecl::setType(SyntaxTree::Type *type) {
    FunctionDecl::type = type;
}

void SyntaxTree::FunctionDecl::handleClassHierarchy() {
    if (this->getType() != nullptr)
        this->getType()->handleClassHierarchy();
    this->getFormals()->handleClassHierarchy();
    this->getStmtBlock()->handleClassHierarchy();
}

SyntaxTree::Cgen SyntaxTree::FunctionDeclToVoidIdent::cgen() {
    return FunctionDecl::cgen();
}
