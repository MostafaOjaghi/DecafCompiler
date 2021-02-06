//
// Created by shengdebao on 2/5/21.
//

#include "WhileStmt.h"

SyntaxTree::Expr *SyntaxTree::WhileStmt::getConditionalExpr() const {
    return conditionalExpr;
}

void SyntaxTree::WhileStmt::setConditionalExpr(SyntaxTree::Expr *conditionalExpr) {
    WhileStmt::conditionalExpr = conditionalExpr;
}

SyntaxTree::Stmt *SyntaxTree::WhileStmt::getStmt() const {
    return stmt;
}

void SyntaxTree::WhileStmt::setStmt(SyntaxTree::Stmt *stmt) {
    WhileStmt::stmt = stmt;
}
