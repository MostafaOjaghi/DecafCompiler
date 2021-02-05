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
