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

void SyntaxTree::ReturnStmt::handleScope() {
    expr->setScope(getScope());
    expr->handleScope();
}

SyntaxTree::Cgen SyntaxTree::ReturnStmt::cgen() {
    Cgen cgen;
    Cgen expr_cgen = expr->cgen();
    cgen.append(expr_cgen);
    cgen.append("Endfunc " + expr_cgen.var + "\n");
    return cgen;
}
