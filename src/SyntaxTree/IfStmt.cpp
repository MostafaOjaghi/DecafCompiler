//
// Created by shengdebao on 2/5/21.
//

#include "IfStmt.h"

SyntaxTree::Expr *SyntaxTree::IfStmt::getConditionalExpr() const {
    return conditionalExpr;
}

void SyntaxTree::IfStmt::setConditionalExpr(SyntaxTree::Expr *conditionalExpr) {
    IfStmt::conditionalExpr = conditionalExpr;
}

SyntaxTree::Stmt *SyntaxTree::IfStmt::getTrueStmt() const {
    return trueStmt;
}

void SyntaxTree::IfStmt::setTrueStmt(SyntaxTree::Stmt *trueStmt) {
    IfStmt::trueStmt = trueStmt;
}

SyntaxTree::Stmt *SyntaxTree::IfStmt::getFalseStmt() const {
    return falseStmt;
}

void SyntaxTree::IfStmt::setFalseStmt(SyntaxTree::Stmt *falseStmt) {
    IfStmt::falseStmt = falseStmt;
}
