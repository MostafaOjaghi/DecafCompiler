//
// Created by shengdebao on 2/5/21.
//

#include "Stmts.h"

const std::vector<SyntaxTree::Stmt *> &SyntaxTree::Stmts::getStmts() const {
    return stmts;
}

void SyntaxTree::Stmts::addStmt(SyntaxTree::Stmt *stmt) {
    stmts.push_back(stmt);
}

SyntaxTree::Cgen SyntaxTree::Stmts::cgen() {
    Cgen cgen;
    for (Stmt *stmt : stmts)
        cgen.code += stmt->cgen().code;
    return cgen;
}

void SyntaxTree::Stmts::handleScope() {
    for (Stmt *stmt : stmts) {
        stmt->setScope(this->getScope());
        stmt->handleScope();
    }

}
