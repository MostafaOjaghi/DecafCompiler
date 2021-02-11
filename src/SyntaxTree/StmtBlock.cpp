//
// Created by shengdebao on 2/5/21.
//

#include "StmtBlock.h"

SyntaxTree::Stmts *SyntaxTree::StmtBlock::getStmts() const {
    return stmts;
}

void SyntaxTree::StmtBlock::setStmts(SyntaxTree::Stmts *stmts) {
    StmtBlock::stmts = stmts;
}

SyntaxTree::VariableDecls *SyntaxTree::StmtBlock::getVariableDecls() const {
    return variableDecls;
}

void SyntaxTree::StmtBlock::setVariableDecls(SyntaxTree::VariableDecls *variableDecls) {
    StmtBlock::variableDecls = variableDecls;
}

SyntaxTree::Cgen SyntaxTree::StmtBlock::cgen() {
    //TODO handle variables
    Cgen cgen;
    cgen.append(variableDecls->cgen());
    cgen.append(stmts->cgen());
    return cgen;
}

void SyntaxTree::StmtBlock::handleScope() {
    this->getVariableDecls()->setScope(this->getScope());
    this->getVariableDecls()->handleScope();
    auto *stmtsScope = new SymbolTable::Scope("stmts", this->getScope());
    this->getStmts()->setScope(stmtsScope);
    this->getStmts()->handleScope();
}
