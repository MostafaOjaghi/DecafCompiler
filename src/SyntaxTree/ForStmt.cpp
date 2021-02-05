//
// Created by shengdebao on 2/5/21.
//

#include "ForStmt.h"

SyntaxTree::Expr *SyntaxTree::ForStmt::getForInit() const {
    return forInit;
}

void SyntaxTree::ForStmt::setForInit(SyntaxTree::Expr *forInit) {
    ForStmt::forInit = forInit;
}

SyntaxTree::Expr *SyntaxTree::ForStmt::getForCondition() const {
    return forCondition;
}

void SyntaxTree::ForStmt::setForCondition(SyntaxTree::Expr *forCondition) {
    ForStmt::forCondition = forCondition;
}

SyntaxTree::Expr *SyntaxTree::ForStmt::getForStep() const {
    return forStep;
}

void SyntaxTree::ForStmt::setForStep(SyntaxTree::Expr *forStep) {
    ForStmt::forStep = forStep;
}

SyntaxTree::Stmt *SyntaxTree::ForStmt::getStmt() const {
    return stmt;
}

void SyntaxTree::ForStmt::setStmt(SyntaxTree::Stmt *stmt) {
    ForStmt::stmt = stmt;
}
