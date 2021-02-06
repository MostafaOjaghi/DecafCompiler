//
// Created by shengdebao on 2/5/21.
//

#include "ReturnStmt.h"

SyntaxTree::Expr *SyntaxTree::ReturnStmt::getExpr() const {
    return expr;
}

void SyntaxTree::ReturnStmt::setExpr(SyntaxTree::Expr *expr) {
    ReturnStmt::expr = expr;
}
